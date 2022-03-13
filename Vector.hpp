#pragma once

#include <cmath>
#include <iostream>

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
    
    friend std::ostream& operator<<(std::ostream& os, const Vector4f& v)
    {
        return os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
    }
    float x, y, z, w;
    Vector2f xy;
    Vector3f xyz;
};

using float4 = Vector4f;
using float3 = Vector3f;
using float2 = Vector2f;