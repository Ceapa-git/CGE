#ifndef __VEC4__H__
#define __VEC4__H__

#include "vec3.h"

namespace cge::math
{
    template <typename T>
    struct vec4
    {
        T x, y;

        vec4();
        vec4(T x, T y);
        vec4(const vec4& other);

        bool operator==(const vec4& other) const;

        vec4& operator=(const vec4& other);
        vec4& operator+=(const vec4& other);
        vec4& operator-=(const vec4& other);
        vec4& operator*=(T scalar);

        vec4 operator+(const vec4 &other)const;
        vec4 operator-(const vec4 &other)const;
        vec4 operator*(T scalar)const;
        vec4 operator-()const;
    };

    typedef vec4<int> vec4i;
    typedef vec4<float> vec4f;
    typedef vec4<double> vec4d;
}

#endif //__VEC4__H__