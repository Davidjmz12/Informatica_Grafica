#pragma once

#include <array>

#include "scene/ray.hpp"

class BoundingBox {
private:

    std::array<double, 6> _bound_box;
public:

    static BoundingBox get_BB_by_corners(const std::vector<Point>& corners);
    static BoundingBox combine_all(const std::vector<BoundingBox> geometries);

    double center(size_t axis) const;

    BoundingBox();

    BoundingBox(const std::array<double, 6>& bounds);

    bool intersect_with_ray(const Ray& ray) const;

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bb);
};