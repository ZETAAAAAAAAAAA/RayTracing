#include "Vector.hpp"
#include "Triangle.hpp"
#include "Texture.hpp"
#include <vector>

struct VertexShaderCalculateData{
    VertexShaderCalculateData (const float3& wnor, const float3& wpos, const float4& cpos, const float2& texcoord):
    worldNormal(wnor), worldPos(wpos), clipPos(cpos), uv(texcoord){}

    float4 clipPos;
    float3 worldNormal;
    float3 worldPos;
    float2 uv;
};

class Render
{
public:
    Render(int w, int h): width(w), height(h) { frameBuffer.resize(w * h); depthBuffer.resize(w * h);};
    int getIndex (int x, int y) { return y * width + x; };
    float4 getColor(int x ,int y) { int index = getIndex(x, y); return frameBuffer[index]; };
    void clear() 
    { 
        std::fill(frameBuffer.begin(), frameBuffer.end(), float4(0, 0, 0, 0)); 
        std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::infinity());
    }

    void setModelMatrix(float4x4 m) { modelMatrix = m; }
    void setViewMatrix(float4x4 v) { viewMatrix = v; } 
    void setProjectionMatrix(float4x4 p) { projectionMatirx = p; }
    void setMVP_Matrix(float4x4 m, float4x4 v, float4x4 p)  { MVP_MATRIX = mul(p, mul(v, m)); }

    void setViewPos(const float3& viewPos) { worldSpaceViewPos = viewPos; }
    void setLightPos(const float3& lightPos) { worldSpaceLightPos = lightPos;}
    void setTexture(Texture* tex) { _MainTex = tex; }

    void renderModel(std::vector<Triangle *> &TriangleList) { vertexShader(TriangleList); };
    void vertexShader(std::vector<Triangle *> &TriangleList);
    void rasterizeTriangle(std::vector<VertexShaderCalculateData> &i);
    float4 fragmentShader(const VertexShaderCalculateData& i);
    
public:
    int width, height;
    std::vector<float> depthBuffer;
    std::vector<float4> frameBuffer;
    
    float4x4 modelMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatirx;
    float4x4 MVP_MATRIX;
    
    Texture* _MainTex;
    //direction light 
    float3 worldSpaceLightPos;
    float3 worldSpaceViewPos;
};