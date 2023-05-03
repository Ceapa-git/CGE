#ifndef __VEC2__H__
#define __VEC2__H__

#include "vec3.h"

namespace cge::math
{
    template <typename T>
    struct vec2
    {
        T x, y;

        vec2();
        vec2(T x, T y);
        vec2(const vec2& other);
        vec2(const vec3<T>& other);

        bool operator==(const vec2& other) const;

        vec2& operator=(const vec2& other);
        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(T scalar);

        vec2 operator+(const vec2 &other)const;
        vec2 operator-(const vec2 &other)const;
        vec2 operator*(T scalar)const;
        vec2 operator-()const;
    };

    typedef vec2<int> vec2i;
    typedef vec2<float> vec2f;
    typedef vec2<double> vec2d;
}

#endif //__VEC2__H__