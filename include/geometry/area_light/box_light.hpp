#pragma once

#include "geometry/area_light/area_light.hpp"
#include "geometry/box.hpp"

class BoxLight : public AreaLight
{
private:
    Box _box;

public:
    BoxLight(Box box, SpectralColor power);

    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const override;

    std::string to_string() const override;
};
