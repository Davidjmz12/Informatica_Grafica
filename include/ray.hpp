#pragma once

#include "geometry.hpp"

class Ray
{
private:
    Geometric _point;
    Geometric _direction;
    
public:
    Ray(Geometric point, Geometric direction);
    Geometric point() const;
    Geometric direction() const;

    Geometric evaluate_point(float t) const;
    bool intersects_with_geometry(Geometry* g, Intersection& intersection);
};
