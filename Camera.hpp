// prespective camera
#include "Vector.hpp"

struct Camera
{
    Camera(const float3& pos, const float3& rota, float near, float far, float fov ,float rati):
    position(pos), rotation(rota), zNear(near), zFar(far), FOV(fov), aspectRatio(rati) {}

    //World Space
    float3 position;
    //thetaX, thetaY, thetaZ 
    float3 rotation;
    float zNear;
    float zFar;
    float FOV;
    float aspectRatio;
};