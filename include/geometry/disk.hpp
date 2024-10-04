#pragma once 

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

class Disk: public Geometry
{
private:
    Plane _plane;
    float _radius;
public:
    Disk(Geometric center, Geometric normal, float radius);

    float implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

};
