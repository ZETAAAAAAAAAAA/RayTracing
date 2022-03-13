#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H

class Triangle{
public:
    float4 vertex[3];
    float4 color[3];
    float2 texcoord[3];
    float3 normal[3];

public:
    Triangle();
    void setVertex(int index, float4 ver);
    void setNormal(int index, float3 nor);
    void setColor(int index, float4 col);
    void setTexcoord(int index, float2 uv);

};
#endif