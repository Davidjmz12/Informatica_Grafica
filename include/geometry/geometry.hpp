#pragma once

#include "intersection.hpp"
#include "ray.hpp"
#include "geometric.hpp"

class Geometry
{
public:
    virtual bool intersect_with_ray(Ray r, Intersection& intersection) const = 0; 
};
