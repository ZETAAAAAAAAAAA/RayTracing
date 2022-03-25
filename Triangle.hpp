#ifndef RASTERIZER_TRIANGLE_H
#define RASTERIZER_TRIANGLE_H
#include "Vector.hpp"

class Triangle{
public:
    float4 vertex[3];
    float4 color[3];
    float2 texcoord[3];
    float3 normal[3];

public:
    Triangle(){
        vertex[0] = float4(0,0,0,1);
        vertex[1] = float4(0,0,0,1);
        vertex[2] = float4(0,0,0,1);
    }

    //load models
    void setVertex(int index, float4 ver) { vertex[index] = ver; }
    void setNormal(int index, float3 nor) { normal[index] = nor; }
    void setColor(int index, float4 col) { color[index] = col; }
    void setTexCoord(int index, float2 uv) { texcoord[index] = uv; }
};
#endif