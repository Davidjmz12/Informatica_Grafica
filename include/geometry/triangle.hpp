#pragma once

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

class Triangle : Geometry
{
private:
    Geometric _v0;
    Geometric _v1;
    Geometric _v2;

    bool point_inside_triangle(Geometric p) const;
public:

    Triangle(Geometric v0, Geometric v1, Geometric v2);

    Geometric normal() const;
    Plane plane() const ;
    
    float implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};