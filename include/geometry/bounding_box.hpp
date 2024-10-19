#pragma once

#include <array>
#include "ray.hpp"

class BoundingBox {
private:

    std::array<double, 6> _bound_box;
public:

    // Constructor that accepts a std::array<double, 6>
    BoundingBox(const std::array<double, 6>& bounds);

    // Function to check if a ray intersects the bounding box
    bool intersects_with_ray(const Ray& ray) const;
};