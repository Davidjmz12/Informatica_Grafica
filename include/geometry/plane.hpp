#pragma once

#include "geometry.hpp"

class Plane : Geometry
{
private:
    Geometric _normal;
    Geometric _point;
    float _d;
public:
    Plane(Geometric normal, Geometric point);
    Plane(Geometric p1, Geometric p2, Geometric p3);

    float implicit(Geometric x) const;

    bool intersect_with_ray(Ray r, Intersection& intersection) const;
};
