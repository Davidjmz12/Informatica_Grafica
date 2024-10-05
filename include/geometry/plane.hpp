#pragma once

#include "geometry/geometry.hpp"

class Plane : Geometry
{
private:
    Geometric _normal;
    Geometric _point;
public:
    Plane(Geometric normal, Geometric point);
    Plane(Geometric p1, Geometric p2, Geometric p3);

    Geometric point() const;

    Geometric normal() const;
    
    float implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};
