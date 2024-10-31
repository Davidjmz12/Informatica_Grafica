#pragma once

#include "color/spectral_color.hpp"
#include "geometry/geometry.hpp"

class PunctualLight
{
private:
    Point _center;
    SpectralColor _power;

public:

    PunctualLight(Point center, SpectralColor power);
    
    SpectralColor light_contribution(std::vector<Geometry*> geometries, const IntersectionObject& intersection, SpectralColor indirect_light) const;
};
