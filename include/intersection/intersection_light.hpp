#pragma once

#include "intersection/intersection.hpp"
#include "color/spectral_color.hpp"


class IntersectionLight : public Intersection
{
private:
    SpectralColor _power;

public:
    IntersectionLight();
        
    IntersectionLight(double distance, SpectralColor power, Point intersection_point, Ray ray);

    SpectralColor get_power() const;

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const IntersectionLight& i);
};
