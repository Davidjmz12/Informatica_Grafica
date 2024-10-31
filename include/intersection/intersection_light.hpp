#pragma once

#include "intersection/intersection.hpp"
#include "color/spectral_color.hpp"
#include "spatial_element/vector.hpp"

class IntersectionLight : public Intersection
{
private:
    SpectralColor _power;
    Vector _origin;

public:
    IntersectionLight()
        : Intersection(std::numeric_limits<double>::max()) {};
    IntersectionLight(double distance, SpectralColor power, Vector origin);

    SpectralColor get_power() const
    {
        return _power;
    }
};
