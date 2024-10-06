#pragma once 

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

class Disk: public Geometry
{
private:
    Plane _plane;
    double _radius;
public:
    Disk(Geometric center, Geometric normal, double radius);

    double implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

};
