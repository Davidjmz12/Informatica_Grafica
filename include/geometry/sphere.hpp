#pragma once

#include "geometry.hpp"

class Sphere : Geometry
{
private:
    Geometric _center;
    float _radius;
public:
    Sphere(Geometric center, float radius);
    
    float implicit(Geometric x) const;

    bool intersect_with_ray(Ray r, Intersection& intersection) const;
};
