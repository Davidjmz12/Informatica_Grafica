#pragma once

#include "intersection.hpp"

class Ray
{
private:
    Geometric _point;
    Geometric _direction;
    
public:
    Ray(Geometric point, Geometric direction);
    Geometric point() const;
    Geometric direction() const;
};
