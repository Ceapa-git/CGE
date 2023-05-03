#ifndef __VEC3__H__
#define __VEC3__H__

#include "vec4.h"

namespace cge::math
{
    template <typename T>
    struct vec3
    {
        T x, y,z;

        vec3();
        vec3(T x, T y,T z);
        vec3(const vec3& other);
        vec3(const vec4<T>& other);

        bool operator==(const vec3& other) const;

        vec3& operator=(const vec3& other);
        vec3& operator+=(const vec3& other);
        vec3& operator-=(const vec3& other);
        vec3& operator*=(T scalar);

        vec3 operator+(const vec3 &other)const;
        vec3 operator-(const vec3 &other)const;
        vec3 operator*(T scalar)const;
        vec3 operator-()const;
    };

    typedef vec3<int> vec3i;
    typedef vec3<float> vec3f;
    typedef vec3<double> vec3d;
}

#endif //__VEC3__H__