#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <random>
#include "Vector.hpp"
#include "Rasterizer.hpp"

using namespace std;

int main()
{
    int width = 200;
    int height = 100;
	
    Rasterizer r(100, 100);
    cout << "r" << r.getColor(1,2) << "\n255\n";

    float3 test = float3(0,0,0);
    test.x = 1;
    cout << "test" << test << "\n255\n";

    ofstream outfile( "mytest.txt", ios_base::out);
    outfile << "P3\n" << width << " " << height << "\n255\n";

    cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float r = float(i) / float(width);
            float g = float(j) / float(height);
            float b = 0.2;
            int ir = int (255.99*r);
            int ig = int (255.99*g);
            int ib = int (255.99*b);
          
            //float3 color = r.getColor(i,j);
            //int ir = int (255 * color.x);
            //int ig = int (255 * color.y);
            //int ib = int (255 * color.z);
            
            outfile << ir << " " << ig << " " << ib << "\n";
            //std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
