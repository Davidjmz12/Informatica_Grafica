#pragma once

#include "color.hpp"
#include "geometry/geometry.hpp"

class Light
{
private:
    Point _center;
    Color _power;

public:

    Light(Point center, Color power);
    
    bool meets_light(std::vector<Geometry*> geometries, const Intersection& intersection) const;
};
