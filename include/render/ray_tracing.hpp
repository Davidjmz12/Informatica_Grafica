#pragma once

#include "render/render.hpp"

class RayTracing final : public Render {

private:

    [[nodiscard]] Color compute_ray_intersection_color(const Ray& r, size_t n_rec) const;
    [[nodiscard]] Color compute_ray_color(const Ray& r) const override;

    void init_render() override;
public:
	explicit RayTracing(Scene& s);
};

