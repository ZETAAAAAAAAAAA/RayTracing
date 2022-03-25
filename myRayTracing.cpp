#include <iostream>
#include "Vector.hpp"
#include "Triangle.hpp"
#include "OBJ_Loader.h"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Render.hpp"
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Eigen>
using namespace std;

int main(int argc, const char** argv)
{   
    int width = 1024;
    int height = 512;

    vector<Triangle*> TriangleList;

    string filename = "output.png";
    objl::Loader Loader;
    string obj_path = "../models";

    bool loadout = Loader.LoadFile("../models/spot_triangulated_good.obj");
    for(auto mesh:Loader.LoadedMeshes)
    {
        for(int i=0;i<mesh.Vertices.size();i+=3)
        {
            Triangle* t = new Triangle();
            for(int j=0;j<3;j++)
            {
                t->setVertex(j,float4(mesh.Vertices[i+j].Position.X,mesh.Vertices[i+j].Position.Y,mesh.Vertices[i+j].Position.Z,1.0));
                t->setNormal(j,float3(mesh.Vertices[i+j].Normal.X,mesh.Vertices[i+j].Normal.Y,mesh.Vertices[i+j].Normal.Z));
                t->setTexCoord(j,float2(mesh.Vertices[i+j].TextureCoordinate.X, mesh.Vertices[i+j].TextureCoordinate.Y));
            }
            TriangleList.push_back(t);
        }
    }
    
    Camera cam(float3(0,10,-10), float3(10,0,0), 5, 40, 60, 2);

    Render* r = new Render(width, height);
    
    int X = 0;
    int Y = 0;
    int Z = 0;
    int key = 0; 
    int sacle = 5;
    while ( key != 5)
    {
        r->clear();

        r->setModelMatrix(objectToWorldMatrix(float3(0,6.5,0), float3(0,40,0), float3(sacle)));
        r->setViewMatrix(worldToViewMatix( -cam.position, -cam.rotation));
        r->setProjectionMatrix(viewToClipMatrix(cam.FOV, cam.aspectRatio, cam.zNear, cam.zFar));
        r->setMVP_Matrix(r->modelMatrix, r->viewMatrix, r->projectionMatirx);

        Texture* mainTex = new Texture("../models/spot_texture.png");
        r->setTexture(mainTex);
        r->setLightPos(float3(0,0,1));
        r->setViewPos(cam.position);

        r->renderModel(TriangleList);

        cv::Mat image(height, width, CV_32FC3, r->frameBuffer.data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);
        
        if (key == 'w') {
            X += 10;
        }
        else if (key == 's') {
            X -= 10;
        }
        else if (key == 'a') {
            Y -= 10;
        }
        else if (key == 'd') {
            Y += 10;
        }
        else if (key == 'q') {
            Z += 10;
        }        
        else if (key == 'e') {
            Z += 10;
        }

        ofstream outfile( "mytest.ppm", ios_base::out);
        outfile << "P3\n" << width << " " << height << "\n255\n";

        cout << "P3\n" << width << " " << height << "\n255\n";
        for (int j = height-1; j > 0; j--)
        {
            for (int i = 0; i < width; i++)
            {   
                
                float4 color = r->getColor(i, j);    
                int ir = int (255 * color.x);
                int ig = int (255 * color.y);
                int ib = int (255 * color.z);
                
                outfile << ir << " " << ig << " " << ib << "\n";
                //cout << ir << " " << ig << " " << ib << "\n";
            }
        }
    } 

    delete(r);
    return 0;
}
