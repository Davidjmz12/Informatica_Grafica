#pragma once 

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

class Disk: public Geometry
{
private:
    Plane _plane;
    double _radius;
public:
    Disk(Point center, Vector normal, double radius);

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

};
