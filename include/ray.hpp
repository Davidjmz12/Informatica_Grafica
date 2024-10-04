#pragma once

#include "intersection.hpp"

class Ray
{
private:
    Geometric _point;
    Geometric _direction;
    
public:
    Ray(Geometric point, Geometric direction);
    Geometric evaluate(float t) const;
    Geometric point() const;
    Geometric direction() const;

    Geometric evaluate_point(float t) const;
};
