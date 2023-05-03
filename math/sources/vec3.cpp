#include "pch.h"
#include "vec3.h"
#include "vec4.h"

namespace cge::math
{
    template <typename T>
    vec3<T>::vec3()
    {
        x = y = z = (T)0;
    }
    template <typename T>
    vec3<T>::vec3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    template <typename T>
    vec3<T>::vec3(const vec3<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }
    template <typename T>
    vec3<T>::vec3(const vec4<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    template <typename T>
    bool vec3<T>::operator==(const vec3<T> &other) const
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    template <typename T>
    vec3<T> &vec3<T>::operator=(const vec3<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
    }
    template <typename T>
    vec3<T> &vec3<T>::operator+=(const vec3<T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
    template <typename T>
    vec3<T> &vec3<T>::operator-=(const vec3<T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }
    template <typename T>
    vec3<T> &vec3<T>::operator*=(T scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    template <typename T>
    vec3<T> vec3<T>::operator+(const vec3<T> &other) const
    {
        vec3 res(*this);
        res.x += other.x;
        res.y += other.y;
        res.z += other.z;
        return res;
    }
    template <typename T>
    vec3<T> vec3<T>::operator-(const vec3<T> &other) const
    {
        vec3 res(*this);
        res.x -= other.x;
        res.y -= other.y;
        res.z -= other.z;
        return res;
    }
    template <typename T>
    vec3<T> vec3<T>::operator*(T scalar) const
    {
        vec3 res(*this);
        res.x *= scalar;
        res.y *= scalar;
        res.z *= scalar;
        return res;
    }
    template <typename T>
    vec3<T> vec3<T>::operator-() const
    {
        vec3 res;
        res.x = -this->x;
        res.y = -this->y;
        res.z = -this->z;
        return res;
    }
}