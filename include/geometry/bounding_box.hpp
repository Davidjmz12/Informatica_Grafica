#pragma once

#include <array>

#include "scene/ray.hpp"

/**
 * @brief Class that represents a bounding box.
 *
 * This class represents a bounding box, which is a box that contains
 * a geometry. This box is defined by two points, the minimum and maximum
 * points of the box.
 */
class BoundingBox {
private:
    std::array<double, 6> _bound_box;
public:

    /**
    * @brief Get a bounding box by the corners of an object.
    *
    * @param corners The corners of the object.
    */
    static BoundingBox get_BB_by_corners(const std::vector<Point>& corners);


    static BoundingBox combine_all(const std::vector<BoundingBox>& geometries);

    BoundingBox();

    explicit BoundingBox(const std::array<double, 6>& bounds);


    [[nodiscard]] double center(size_t axis) const;

    [[nodiscard]] bool intersect_with_ray(const Ray& ray) const;



    [[nodiscard]] std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bb);
};