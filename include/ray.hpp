#pragma once

#include "intersection.hpp"

class Ray
{
private:
    Point _point;
    Vector _direction;
    
public:
    Ray(Point point, Vector direction);
    Point evaluate(float t) const;
    Point get_point() const;
    Vector get_direction() const;
};
