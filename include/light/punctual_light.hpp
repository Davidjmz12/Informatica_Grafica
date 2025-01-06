#pragma once

#include "color/color.hpp"
#include "geometry/geometry.hpp"
#include "geometry/kd-trees/kd-tree.hpp"
#include "light/abstract_light.hpp"

class PunctualLight : public AbstractLight
{
private:
    Point _center;
    Color _power;

public:

    PunctualLight(Point center, const Color& power);
    PunctualLight() = default;

    Ray sample_ray() const override;

    [[nodiscard]] double luminance_mean() const;
    [[nodiscard]] double luminance_max() const;
    [[nodiscard]] Color light_contribution(const KDTree& tree, const IntersectionObject& intersection, BRDFType type) const;

};
