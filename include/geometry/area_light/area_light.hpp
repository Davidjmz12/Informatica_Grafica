#pragma once

#include "color/spectral_color.hpp"
#include "scene/intersection.hpp"
#include "scene/ray.hpp"

class AreaLight
{
protected:
    SpectralColor _power;

public:
    AreaLight(SpectralColor power)
        : _power(power) {};

    virtual bool intersect_with_ray(const Ray& r, Intersection& intersection) const = 0;

    virtual std::string to_string() const = 0;
};
