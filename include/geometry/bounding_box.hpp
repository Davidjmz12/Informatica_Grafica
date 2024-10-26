#pragma once

#include <array>

#include "ray.hpp"

class BoundingBox {
private:

    std::array<double, 6> _bound_box;
public:

    static BoundingBox get_BB_by_corners(const std::vector<Point>& corners);

    BoundingBox();

    BoundingBox(const std::array<double, 6>& bounds);

    bool intersect_with_ray(const Ray& ray) const;
};