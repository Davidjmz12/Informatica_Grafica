#ifndef POINT_HPP
#define POINT_HPP

#include "vector.hpp"
#include <iostream>

class Vector;

class Point
{
private:
    float coord[3];
public:

    Point(float x, float y, float z);

    Point operator+(Vector const v) const;
    Vector operator-(Point const p) const;
    Point operator*(float scalar) const;
    Point operator/(float scalar) const;
    bool operator==(Point const p) const;

    friend std::ostream& operator<<(std::ostream& os,const Point& p);

};

#endif