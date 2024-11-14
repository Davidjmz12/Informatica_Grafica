#pragma once

#include "render/render.hpp"

class RayTracing final : public Render {

private:

    [[nodiscard]] SpectralColor compute_ray_intersection_color(const Ray& r, size_t n_rec) const;
    [[nodiscard]] SpectralColor calculate_punctual_light_contribution(const IntersectionObject& intersection) const;
    [[nodiscard]] SpectralColor compute_ray_color(const Ray& r) const override;
public:

	explicit RayTracing(Scene& s);
};

