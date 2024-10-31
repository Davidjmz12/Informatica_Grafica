#pragma once

#include "intersection/intersection.hpp"
#include "color/spectral_color.hpp"


class IntersectionLight : public Intersection
{
private:
    SpectralColor _power;

public:
    IntersectionLight();
        
    IntersectionLight(double distance, SpectralColor power, Vector origin);

    SpectralColor get_power() const;
};
