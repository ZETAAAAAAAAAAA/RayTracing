#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Vector.hpp"

constexpr double MY_PI = 3.1415926;

//angle
inline float4x4 getRotationMatrix (float x,float y,float z)
{   
    x = x / 180.0f * MY_PI;
    y = y / 180.0f * MY_PI;
    z = z / 180.0f * MY_PI;
    float4x4 rotationX = float4x4(1.0f,0.0f,0.0f,0.0f,
                                  0.0f,cos(x),-sin(x),0.0f,
                                  0.0f,sin(x),cos(x),0.0f,
                                  0.0f,0.0f,0.0f,1.0f);
    
    float4x4 rotationY = float4x4(cos(y),0.0f,sin(y),0.0f,
                                  0.0f,1.0f,0.0f,0.0f,
                                  -sin(y),0.0f,cos(y),0.0f,
                                  0.0f,0.0f,0.0f,1.0f);
    
    float4x4 rotationZ = float4x4(cos(z),-sin(z),0.0f,0.0f,
                                  sin(z),cos(z),0.0f,0.0f,
                                  0.0f,0.0f,1.0f,0.0f,
                                  0.0f,0.0f,0.0f,1.0f);

    float4x4 rotation = mul(rotationZ, mul(rotationX, rotationY));
    return rotation;
}

inline float4x4 objectToWorldMatrix (const float3& translation, const float3& rotation, const float3& scale)
{
    float4x4 scaleMatrix = float4x4(scale.x,0.0f,0.0f,0.0f,
                                    0.0f,scale.y,0.0f,0.0f,
                                    0.0f,0.0f,scale.z,0.0f,
                                    0.0f,0.0f,0.0f,1.0f);

    float4x4 rotationMatrix = getRotationMatrix(rotation.x,rotation.y,rotation.z);
    
    float4x4 translationMatrix = float4x4(1.0f,0.0f,0.0f,translation.x,
                                           0.0f,1.0f,0.0f,translation.y,
                                           0.0f,0.0f,1.0f,translation.z,
                                           0.0f,0.0f,0.0f,1.0f);
    
    float4x4 modelMatrix = mul(translationMatrix, mul(rotationMatrix, scaleMatrix));
    return modelMatrix;
}

// Camera Transform
inline float4x4  worldToViewMatix (const float3& translation, const float3& rotation)
{
    // right hand
    float4x4 nsgats = float4x4(1.0f,0.0f,0.0f,0.0f,
                               0.0f,1.0f,0.0f,0.0f,
                               0.0f,0.0f,-1.0f,0.0f,
                               0.0f,0.0f,0.0f,1.0f);

    float4x4 rotationMatrix = getRotationMatrix(rotation.x,rotation.y,rotation.z);
    
    float4x4 translationMatrix = float4x4(1.0f,0.0f,0.0f,translation.x,
                                           0.0f,1.0f,0.0f,translation.y,
                                           0.0f,0.0f,1.0f,translation.z,
                                           0.0f,0.0f,0.0f,1.0f);

    float4x4 viewMatrix = mul(nsgats,mul(rotationMatrix,translationMatrix));
    return viewMatrix;
}
inline float cot(float a)
{
    return 1.0f/tan(a);
}
//angle
inline float4x4  viewToClipMatrix(float FOV, float aspectRatio, float zNear, float zFar)
{
    FOV = FOV / 180.0f * MY_PI;
    float4x4 projectionMatirx = float4x4(cot(FOV/2)/aspectRatio,0.0f,0.0f,0.0f,
                                          0.0f,cot(FOV/2),0.0f,0.0f,
                                          0.0f,0.0f,(zNear+zFar)/(zNear-zFar),2*zNear*zFar/(zNear-zFar),
                                          0.0f,0.0f,-1.0f,0.0f);

    return projectionMatirx;
}

//[0.0f,1.0f]
inline float2 computeScreenPos (const float4& clipPos)
{
    float2 screenPos = float2(clipPos.x/clipPos.w, clipPos.y/clipPos.w) *0.5f +0.5f;
    return screenPos;
}

inline float3 reflect(const float3& vec, float3& axis)
{
    auto costheta = dot(vec, axis);
    return normalize(2 * costheta * axis - vec);
}

#endif