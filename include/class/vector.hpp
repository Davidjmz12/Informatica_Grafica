#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "point.hpp"
#include <iostream>

class Point;

class Vector
{
public:
    float coord[3];

    Vector(float x,float y,float z);

    Vector operator+(Vector const v) const;
    Vector operator-(Vector const v) const;
    Vector operator*(float scalar) const;
    Vector operator/(float scalar) const;
    bool operator==(Vector const v) const;

    float norm() const;
    Vector normalize() const;
    float dot(Vector const v) const;
    Vector cross(Vector const v) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

};

#endif