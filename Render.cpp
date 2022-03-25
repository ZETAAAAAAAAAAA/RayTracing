#include "Render.hpp"
#include <tuple>
#include "Transform.hpp"
using namespace std;

// v:[0,width] [0,height]
static tuple<float, float, float> computeBarycentric2D(float x, float y, const float2* v)
{
    float c1 = (x*(v[1].y - v[2].y) + (v[2].x - v[1].x)*y + v[1].x*v[2].y - v[2].x*v[1].y) / (v[0].x*(v[1].y - v[2].y) + (v[2].x - v[1].x)*v[0].y + v[1].x*v[2].y - v[2].x*v[1].y);
    float c2 = (x*(v[2].y - v[0].y) + (v[0].x - v[2].x)*y + v[2].x*v[0].y - v[0].x*v[2].y) / (v[1].x*(v[2].y - v[0].y) + (v[0].x - v[2].x)*v[1].y + v[2].x*v[0].y - v[0].x*v[2].y);
    float c3 = (x*(v[0].y - v[1].y) + (v[1].x - v[0].x)*y + v[0].x*v[1].y - v[1].x*v[0].y) / (v[2].x*(v[0].y - v[1].y) + (v[1].x - v[0].x)*v[2].y + v[0].x*v[1].y - v[1].x*v[0].y); 

    return {c1,c2,c3};
}

// v:[0,width] [0,height]
static bool insideTriangle(double x, double y, const float2* v)
{   
	float2 p = float2(x,y);
    
    float2 PA = v[0] - p;
    float2 PB = v[1] - p;
    float2 PC = v[2] - p;

    return cross(PA,PB) < 0 && cross(PB,PC) < 0 && cross(PC,PA) < 0;
   // return (cross(PA,PB) < 0 && cross(PB,PC) < 0 && cross(PC,PA) < 0) || (cross(PA,PB) > 0 && cross(PB,PC) > 0 && cross(PC,PA) > 0);
}

//uv: [0,1] getColor: [0,255]
static float3 tex2D(Texture* tex, const float2& uv)
{
    if (uv.x > 1 || uv.y >1 )
    {
        return float3(0.0f,0.0f,0.0f);
    } 
    return tex->getColor(uv.x, uv.y) / 255;
}

static float saturate(float a)
{
    a = std::min(a,1.0f);
    a = std::max(0.0f,a);
    return a;
}

void Render::vertexShader(vector<Triangle *> &TriangleList)
{
    for (const auto& t:TriangleList)
    {
        vector<VertexShaderCalculateData> o;
        for (int i = 0; i < 3; i++)
        {
            float4 clipPos = mul(MVP_MATRIX, t->vertex[i]);
            float3 worldPos = mul(modelMatrix, t->vertex[i]).xyz;

            float4x4 invTransMV = transpose( inverse(MVP_MATRIX));
            float3 worldNormal = mul(invTransMV, float4(t->normal[i], 0.0f)).xyz;

            float2 uv = t->texcoord[i];

            VertexShaderCalculateData temp(worldNormal, worldPos, clipPos, uv);
            o.push_back(temp);
        }
        rasterizeTriangle(o);
    }
}

void Render::rasterizeTriangle(vector<VertexShaderCalculateData> &i) {

    // [0,width] [0,height]
    float2 screenPos[] = {
        float2(computeScreenPos(i[0].clipPos).x * width, computeScreenPos(i[0].clipPos).y * height),
        float2(computeScreenPos(i[1].clipPos).x * width, computeScreenPos(i[1].clipPos).y * height),
        float2(computeScreenPos(i[2].clipPos).x * width, computeScreenPos(i[2].clipPos).y * height),
    };
    
    float min_x = min(screenPos[0].x, min(screenPos[1].x, screenPos[2].x));
    float max_x = max(screenPos[0].x, max(screenPos[1].x, screenPos[2].x));
    float min_y = min(screenPos[0].y, min(screenPos[1].y, screenPos[2].y));
    float max_y = max(screenPos[0].y, max(screenPos[1].y, screenPos[2].y));

    min_x=(int)floor(min_x);
    max_x=(int)ceil(max_x);    
    min_y=(int)floor(min_y);
    max_y=(int)ceil(max_y);

    //rasterization
    for (int x = min_x; x < max_x; x++){
        for (int y = min_y; y < max_y; y++){
            if (getIndex(x,y) >= depthBuffer.size() || getIndex(x,y)< 0){
                continue;
            } 
            if (insideTriangle((float)x+0.5,(float)y+0.5, screenPos))
            {
                auto[alpha, beta, gamma] = computeBarycentric2D(x, y, screenPos);

                //depth, using clip space
                float zInterpolated = alpha*i[0].clipPos.z + beta*i[1].clipPos.z + gamma*i[2].clipPos.z;

                if(depthBuffer[getIndex(x, y)] > zInterpolated){
                    auto interpolatedWorldPos = alpha*i[0].worldPos + beta*i[1].worldPos + gamma*i[2].worldPos;
                    auto interpolatedNormal = alpha*i[0].worldNormal + beta*i[1].worldNormal + gamma*i[2].worldNormal;
                    auto interpolatedTexcoord = alpha*i[0].uv + beta*i[1].uv + gamma*i[2].uv;
                    
                    VertexShaderCalculateData o(interpolatedNormal, interpolatedWorldPos, float4(0,0,0,0), interpolatedTexcoord);
                    
                    depthBuffer[getIndex(x,y)] = zInterpolated;
                    frameBuffer[getIndex(x,y)] = fragmentShader(o);
                } 
            }
        }
    }
}

float4 Render::fragmentShader (const VertexShaderCalculateData& i)
{

    float3 ambient = float3(0.1f, 0.1f, 0.1f);

    float3 viewDir = normalize(worldSpaceViewPos - i.worldPos);
    float3 lightDir = normalize(worldSpaceLightPos - i.worldPos);
    float3 halfDir = normalize(viewDir + lightDir);

    float3 diffuse = saturate(dot(i.worldNormal,lightDir));
    float3 specluar = pow(max(0.0f, dot(i.worldNormal, halfDir)), 5);
 
    float3 col = ambient + diffuse + specluar; 
    
    //cout<<i.uv<<endl;
    //float3 col = tex2D(_MainTex, i.uv);
    
    return float4(col, 1.0f);
}
