#pragma once

#include "intersection.hpp"
#include "ray.hpp"

class Geometry
{
public:

    virtual bool intersect_with_ray(const Ray& r, Intersection& intersection) const = 0; 

};
