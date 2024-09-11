#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "punto.hpp"
#include <iostream>

class Vector
{
public:
    float coord[3];

    Vector(float x,float y,float z);
    ~Vector();

    Vector operator+(Vector const v);
    Vector operator-(Vector const v);
    Vector operator*(float scalar);
    Vector operator/(float scalar);
    float norm() const;
    Vector normalize() const;
    float dot(Vector const v1, Vector const v2);
    Vector cross(Vector const v1, Vector const v2);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

};

#endif