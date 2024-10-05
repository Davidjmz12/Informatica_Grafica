#pragma once

#include "geometry/geometry.hpp"

class Sphere : Geometry
{
private:
    Geometric _center;
    double _radius;
public:
    Sphere(Geometric center, double radius);
    
    double implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};
