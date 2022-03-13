#include "Vector.hpp"
#include "Triangle.hpp"
#include<vector>
using namespace std;

class Rasterizer
{
public:
    Rasterizer(int _width, int _height);
    void rasterizeTriangle(const Triangle& t);
    float3 getColor(int x,int y);


private:
    int width, height;
    int getIndex (int x, int y);
    vector<float> depthBuffer;
    vector<float3> frameBuffer;
    
};