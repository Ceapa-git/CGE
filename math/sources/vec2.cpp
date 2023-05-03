#include "pch.h"
#include "vec2.h"
#include "vec3.h"

namespace cge::math
{
    template <typename T>
    vec2<T>::vec2()
    {
        x = y = (T)0;
    }
    template <typename T>
    vec2<T>::vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    template <typename T>
    vec2<T>::vec2(const vec2<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    template <typename T>
    vec2<T>::vec2(const vec3<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    template <typename T>
    bool vec2<T>::operator==(const vec2<T> &other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    template <typename T>
    vec2<T> &vec2<T>::operator=(const vec2<T> &other)
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    template <typename T>
    vec2<T> &vec2<T>::operator+=(const vec2<T> &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    template <typename T>
    vec2<T> &vec2<T>::operator-=(const vec2<T> &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
    template <typename T>
    vec2<T> &vec2<T>::operator*=(T scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    template <typename T>
    vec2<T> vec2<T>::operator+(const vec2<T> &other) const
    {
        vec2 res(*this);
        res.x += other.x;
        res.y += other.y;
        return res;
    }
    template <typename T>
    vec2<T> vec2<T>::operator-(const vec2<T> &other) const
    {
        vec2 res(*this);
        res.x -= other.x;
        res.y -= other.y;
        return res;
    }
    template <typename T>
    vec2<T> vec2<T>::operator*(T scalar) const
    {
        vec2 res(*this);
        res.x *= scalar;
        res.y *= scalar;
        return res;
    }
    template <typename T>
    vec2<T> vec2<T>::operator-() const
    {
        vec2 res;
        res.x = -this->x;
        res.y = -this->y;
        return res;
    }
}