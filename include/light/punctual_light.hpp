#pragma once

#include "color/color.hpp"
#include "geometry/geometry.hpp"
#include "geometry/kd-trees/kd-tree.hpp"

class PunctualLight
{
private:
    Point _center;
    Color _power;

public:

    PunctualLight(Point center, const Color& power);
    PunctualLight() = default;

    Ray sample_random_unitary_ray() const;

    [[nodiscard]] double luminance_mean() const;
    [[nodiscard]] double luminance_max() const;
    [[nodiscard]] Color light_contribution(const KDTree& tree, const IntersectionObject& intersection) const;

};
