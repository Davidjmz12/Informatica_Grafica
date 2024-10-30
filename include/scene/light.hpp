#pragma once

#include "color/spectral_color.hpp"
#include "geometry/geometry.hpp"

class Light
{
private:
    Point _center;
    SpectralColor _power;

public:

    Light(Point center, SpectralColor power);
    
    SpectralColor light_contribution(std::vector<Geometry*> geometries, const Intersection& intersection) const;
};
