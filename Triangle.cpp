#include"Triangle.hpp"
#include<algorithm>

Triangle:: Triangle(){
    vertex[0] = float4(0,0,0,1);
    vertex[1] = float4(0,0,0,1);
    vertex[2] = float4(0,0,0,1);
}

void Triangle::setVertex(int index, float4 ver){
    vertex[index] = ver;
}

void Triangle::setNormal(int index, float3 nor){
    noemal[index] = nor;
}

void Triangle::setColor(int index, float3 col){
    col.x = std::clamp(0,255);
    col.y = std::clamp(0,255);
    col.z = std::clamp(0,255);
    vertex[index] = ver;
}

void Triangle::setTexcoord(int index, float2 uv){
    texcoord[index] = uv;
}