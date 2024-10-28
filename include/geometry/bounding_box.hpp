#pragma once

#include <array>

#include "scene/ray.hpp"

class BoundingBox {
private:

    std::array<double, 6> _bound_box;
public:

    BoundingBox(const std::array<double, 6>& bounds);

    bool intersect_with_ray(const Ray& ray) const;
};