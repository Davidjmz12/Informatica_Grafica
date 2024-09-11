#ifndef PUNTO_HPP
#define PUNTO_HPP

#include "vector.hpp"
#include <iostream>

class Punto
{
private:
    float coord[3];
public:
    Punto(float x, float y, float z);

    Punto operator+(Vector const v) const;
    Vector operator-(Punto const p) const;
    Punto operator*(float scalar) const;
    Punto operator/(float scalar) const;

    friend std::ostream& operator<<(std::ostream& os,const Punto& p);
};

#endif