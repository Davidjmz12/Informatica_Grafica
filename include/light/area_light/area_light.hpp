#pragma once

#include "color/spectral_color.hpp"
#include "intersection/intersection_light.hpp"
#include "scene/ray.hpp"

class AreaLight
{
protected:
    SpectralColor _power;

public:
    AreaLight(SpectralColor power)
        : _power(power) {};

    virtual bool intersect_with_ray(const Ray& r, IntersectionLight& intersection) const = 0;

    virtual std::string to_string() const = 0;
};
