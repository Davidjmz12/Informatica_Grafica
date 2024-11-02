#pragma once

#include "color/spectral_color.hpp"
#include "intersection/intersection_light.hpp"
#include "scene/ray.hpp"
#include "geometry/all_geometry.hpp"

class AreaLight
{
protected:
    Geometry* _shape;
    SpectralColor _power;

public:
    AreaLight(Geometry* shape, SpectralColor power);

    bool intersect_with_ray(const Ray& r, IntersectionLight& intersection) const;

    std::string to_string() const;
};
