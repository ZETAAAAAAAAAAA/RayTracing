#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

class Vector2f
{
public:
    Vector2f()
        : x(0)
        , y(0)
    {}
    Vector2f(float xx)
        : x(xx)
        , y(xx)
    {}
    Vector2f(float xx, float yy)
        : x(xx)
        , y(yy)
    {}
    Vector2f operator*(const float& r) const
    {
        return Vector2f(x * r, y * r);
    }
    Vector2f operator+(const Vector2f& v) const
    {
        return Vector2f(x + v.x, y + v.y);
    }
    Vector2f operator-(const Vector2f& v) const
    {
        return Vector2f(x - v.x, y - v.y);
    }
    friend Vector2f operator*(const float& r, const Vector2f& v)
    {
        return Vector2f(v.x * r, v.y * r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2f& v)
    {
        return os << v.x << ", " << v.y ;
    }
    float x, y;
};

class Vector3f
{
public:
    Vector3f()
        : x(0)
        , y(0)
        , z(0)
    {}
    Vector3f(float xx)
        : x(xx)
        , y(xx)
        , z(xx)
    {}
    Vector3f(float xx, float yy, float zz)
        : x(xx)
        , y(yy)
        , z(zz)
    {
        xy = Vector2f(x,y);
    }
    Vector3f operator*(const float& r) const
    {
        return Vector3f(x * r, y * r, z * r);
    }
    Vector3f operator/(const float& r) const
    {
        return Vector3f(x / r, y / r, z / r);
    }

    Vector3f operator*(const Vector3f& v) const
    {
        return Vector3f(x * v.x, y * v.y, z * v.z);
    }
    Vector3f operator-(const Vector3f& v) const
    {
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }
    Vector3f operator+(const Vector3f& v) const
    {
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }
    Vector3f operator-() const
    {
        return Vector3f(-x, -y, -z);
    }
    Vector3f& operator+=(const Vector3f& v)
    {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    friend Vector3f operator*(const float& r, const Vector3f& v)
    {
        return Vector3f(v.x * r, v.y * r, v.z * r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector3f& v)
    {
        return os << v.x << ", " << v.y << ", " << v.z;
    }
    float x, y, z;
    Vector2f xy;
};

inline Vector3f lerp(const Vector3f& a, const Vector3f& b, const float& t)
{
    return a * (1 - t) + b * t;
}

inline Vector3f normalize(const Vector3f& v)
{
    float mag2 = v.x * v.x + v.y * v.y + v.z * v.z;
    if (mag2 > 0)
    {
        float invMag = 1 / sqrtf(mag2);
        return Vector3f(v.x * invMag, v.y * invMag, v.z * invMag);
    }

    return v;
}

inline float dot(const Vector3f& a, const Vector3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline float cross(const Vector2f& a, const Vector2f& b)
{
    return a.x * b.y - a.y * b.x;
}
inline Vector3f cross(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

class Vector4f
{
public:
    Vector4f()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    {}
    Vector4f(float xx)
        : x(xx)
        , y(xx)
        , z(xx)
        , w(xx)
    {}
    Vector4f(float xx, float yy, float zz, float ww)
        : x(xx)
        , y(yy)
        , z(zz)
        , w(ww)
    {
        xy = Vector2f(x,y);
        xyz = Vector3f(x,y,z);
    }
    Vector4f(const Vector3f& xxyyzz ,float ww)
        : x(xxyyzz.x)
        , y(xxyyzz.y)
        , z(xxyyzz.z)
        , w(ww)
    {
        xy = Vector2f(xxyyzz.x, xxyyzz.y);
        xyz = Vector3f(xxyyzz.x, xxyyzz.y, xxyyzz.z);
    }

    Vector4f operator*(const float& r) const
    {
        return Vector4f(x * r, y * r, z * r, w * r);
    }
    Vector4f operator/(const float& r) const
    {
        return Vector4f(x / r, y / r, z / r, w / r);
    }
    Vector4f operator*(const Vector4f& v) const
    {
        return Vector4f(x * v.x, y * v.y, z * v.z, w * v.w);
    }
    Vector4f operator-(const Vector4f& v) const
    {
        return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    Vector4f operator+(const Vector4f& v) const
    {
        return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    Vector4f operator-() const
    {
        return Vector4f(-x, -y, -z, -w);
    }
    friend Vector4f operator*(const float& r, const Vector4f& v)
    {
        return Vector4f(v.x * r, v.y * r, v.z * r, v.w * r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector4f& v)
    {
        return os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
    }
    float x, y, z, w;
    Vector2f xy;
    Vector3f xyz;
};

class float4x4
{
public:
    float4x4()
    {
        for (int i=0; i<4; i++)
        {
            matrix[i][i]=1;
        }
    }

    float4x4(float x0, float y0, float z0, float w0,
             float x1, float y1, float z1, float w1,
             float x2, float y2, float z2, float w2,
             float x3, float y3, float z3, float w3)
             
    {
       float tempMatrix[4][4] = {{x0,y0,z0,w0}, {x1,y1,z1,w1},{x2,y2,z2,w2},{x3,y3,z3,w3}};
       memcpy(matrix,tempMatrix,sizeof(tempMatrix));

    }
    float4x4(const float mat[4][4]){
        for (int i= 0 ; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] = mat[i][j];
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const float4x4& v)
    {
        return os << v.matrix[0][0]<< ", " <<v.matrix[0][1]<< ", " <<v.matrix[0][2]<< ", " <<v.matrix[0][3]<< std::endl
                    << v.matrix[1][0]<< ", " <<v.matrix[1][1]<< ", " <<v.matrix[1][2]<< ", " <<v.matrix[1][3]<< std::endl
                    << v.matrix[2][0]<< ", " <<v.matrix[2][1]<< ", " <<v.matrix[2][2]<< ", " <<v.matrix[2][3]<< std::endl
                    << v.matrix[3][0]<< ", " <<v.matrix[3][1]<< ", " <<v.matrix[3][2]<< ", " <<v.matrix[3][3];
    }
    float4x4 operator/(const float& r) const
    {
        float b[4][4] = {0};
        for (int i= 0 ; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                b[i][j] = matrix[i][j] / r;
            }
        }
        return float4x4(b);
    }
    float matrix[4][4];


};
inline Vector4f mul(const float4x4& a, const Vector4f& b)
{
    float c[4] = {0};
    for (int i= 0; i < 4; i++)
    {
        c[i] = a.matrix[i][0] * b.x + a.matrix[i][1] * b.y + a.matrix[i][2] * b.z + a.matrix[i][3] * b.w;
    }
    return Vector4f(c[0],c[1],c[2],c[3]);

}
inline float4x4 mul(const float4x4& a, const float4x4& b)
{
    float c[4][4] = {0};
    for (int i= 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float cur = 0;
            for(int k = 0; k < 4; k++)
            {
                cur += a.matrix[i][k] * b.matrix[k][j];
            }
            c[i][j] = cur;
        }
    }
    return float4x4(c);
}

inline float4x4 transpose(const float4x4& a)
{
    float b[4][4] = {0}; 
    for (int i= 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            b[j][i] = a.matrix[i][j];
        }
    }
    return float4x4(b);
}

// n=3
inline float det (const std::vector<float> &a)
{
    return a[0]*a[4]*a[8] + a[1]*a[5]*a[6] + a[2]*a[3]*a[7] 
         - a[0]*a[5]*a[7] - a[1]*a[3]*a[8] - a[2]*a[4]*a[6];
}
// n=4
inline float det (const float4x4& a)
{
    float d = 0;
    for (int i= 0 ; i < 4; i++)
    {
        std::vector<float> vec;
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (row == 0 || col== i)
                {
                    continue;
                }
                vec.push_back(a.matrix[row][col]);
            }
        }
        d += det(vec) * a.matrix[0][i] * pow(-1,i);
    }
    return d;
}

inline float4x4 adj(const float4x4& a)
{
    float b[4][4] = {0};
    for (int i= 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {    
            std::vector<float> vec;
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    if (row == i || col== j){
                        continue;
                    }
                    vec.push_back(a.matrix[row][col]);
                }
            }
            //tranpose
            b[j][i] = det(vec) * pow(-1, i + j);
        }
    }

    return float4x4(b);

}

inline float4x4 inverse(const float4x4&a)
{
    return adj(a) / det(a);

}

using float4 = Vector4f;
using float3 = Vector3f;
using float2 = Vector2f;