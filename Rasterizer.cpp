#include "Rasterizer.hpp"

Rasterizer::Rasterizer(int _width, int _height) : width(_width), height(_height){
    frameBuffer.resize(_width * _height);
    depthBuffer.resize(_width * _height);
}

int Rasterizer::getIndex (int x, int y){
    return y * width + x;
}

float3 Rasterizer::getColor(int x,int y){
    int index = getIndex(x, y);
    return frameBuffer[index];
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const float4* v){
    float c1 = (x*(v[1].y - v[2].y) + (v[2].x - v[1].x)*y + v[1].x*v[2].y - v[2].x*v[1].y) / (v[0].x*(v[1].y - v[2].y) + (v[2].x - v[1].x)*v[0].y + v[1].x*v[2].y - v[2].x*v[1].y);
    float c2 = (x*(v[2].y - v[0].y) + (v[0].x - v[2].x)*y + v[2].x*v[0].y - v[0].x*v[2].y) / (v[1].x*(v[2].y - v[0].y) + (v[0].x - v[2].x)*v[1].y + v[2].x*v[0].y - v[0].x*v[2].y);
    float c3 = (x*(v[0].y - v[1].y) + (v[1].x - v[0].x)*y + v[0].x*v[1].y - v[1].x*v[0].y) / (v[2].x*(v[0].y - v[1].y) + (v[1].x - v[0].x)*v[2].y + v[0].x*v[1].y - v[1].x*v[0].y);
    return {c1,c2,c3};
}

static bool insideTriangle(double x, double y, const float3* _v)
{   
	float2 p = float2(0,0);

    float2 AB = _v[1].xy - _v[0].xy;
    float2 BC = _v[2].xy - _v[1].xy;
    float2 CA = _v[0].xy - _v[2].xy;

    float2 AP = p - _v[0].xy;
    float2 BP = p - _v[1].xy;
    float2 CP = p - _v[2].xy;

    //a cross b>0 mean right 
	return AB.x * AP.y - AB.y * AP.x > 0 
		&& BC.x * BP.y - BC.y * BP.x > 0
		&& CA.x * CP.y - CA.y * CP.x > 0;
}

void Rasterizer::rasterizeTriangle(const Triangle& t) {
	auto v = t.v
    
    float min_x = min(v[0].x, v[1].x, v[2].x));
    float max_x = max(v[0].x, v[1].x, v[2].x));
    float min_y = min(v[0].y, min(v[1].y, v[2].y));
    float max_y = max(v[0].y, max(v[1].y, v[2].y));

    min_x=(int)floor(min_x);
    max_x=(int)ceil(max_x);    
    min_y=(int)floor(min_y);
    max_y=(int)ceil(max_y);

    //rasterization
    for (int x = min_x; x < max_x; x++){
        for (int y = min_y; y < max_y; y++){
            if (insideTriangle((float)x+0.5,(float)y+0.5, v)){

                auto[alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
                //float w_reciprocal = 1.0/(alpha / v[0].w + beta / v[1].w + gamma / v[2].w);

                //v:clipPos z_int : NDC,[0,1] 
                float z_interpolated = alpha * v[0].z / v[0].w + beta * v[1].z / v[1].w + gamma * v[2].z / v[2].w;

                if(depthBuffer[getIndex(x, y)] > z_interpolated){
                    auto interpolated_color = alpha*t.color[0] + beta*t.color[1] + gamma*t.color[2];
                    auto interpolated_normal = alpha*t.normal[0] + beta*t.normal[1] + gamma*t.normal[2];
                    auto interpolated_texcoords = alpha*t.texcoord[0] + beta*t.texcoord[1] + gamma*t.texcoord[2];

                    depthBuffer[getIndex(x,y)] = z_interpolated;
                    frameBuffer[getIndex(x,y)] = interpolated_color;
                }
            }
        }
    }
} 