#include "pch.h"
#include "vec4.h"

namespace cge::math
{
    template <typename T>
    vec4<T>::vec4()
    {
        x = y z = w = (T)0;
    }
    template <typename T>
    vec4<T>::vec4(T x, T y)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    template <typename T>
    vec4<T>::vec4(const vec4<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
    }

    template <typename T>
    bool vec4<T>::operator==(const vec4<T> &other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
    }

    template <typename T>
    vec4<T> &vec4<T>::operator=(const vec4<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
        return *this;
    }
    template <typename T>
    vec4<T> &vec4<T>::operator+=(const vec4<T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        this->w += other.w;
        return *this;
    }
    template <typename T>
    vec4<T> &vec4<T>::operator-=(const vec4<T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        this->w -= other.w;
        return *this;
    }
    template <typename T>
    vec4<T> &vec4<T>::operator*=(T scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;
        return *this;
    }

    template <typename T>
    vec4<T> vec4<T>::operator+(const vec4<T> &other) const
    {
        vec4 res(*this);
        res.x += other.x;
        res.y += other.y;
        res.z += other.z;
        res.w += other.w;
        return res;
    }
    template <typename T>
    vec4<T> vec4<T>::operator-(const vec4<T> &other) const
    {
        vec4 res(*this);
        res.x -= other.x;
        res.y -= other.y;
        res.z -= other.z;
        res.w -= other.w;
        return res;
    }
    template <typename T>
    vec4<T> vec4<T>::operator*(T scalar) const
    {
        vec4 res(*this);
        res.x *= scalar;
        res.y *= scalar;
        res.z *= scalar;
        res.w *= scalar;
        return res;
    }
    template <typename T>
    vec4<T> vec4<T>::operator-() const
    {
        vec4 res;
        res.x = -this->x;
        res.y = -this->y;
        res.z = -this->z;
        res.w = -this->w;
        return res;
    }
}