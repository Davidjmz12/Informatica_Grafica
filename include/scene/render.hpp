#pragma once

#include "scene/scene.hpp"
#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "color/color_map.hpp"
#include "intersection/intersection_object.hpp"

class Render {
private:
    Scene& _scene;
    GlobalConf* _gc;
    ThreadPool _pool;

    [[nodiscard]] std::vector<SpectralColor> paint_k_pixels(std::array<size_t,2> start, size_t n_pixels) const;
    [[nodiscard]] SpectralColor compute_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] SpectralColor compute_random_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] SpectralColor compute_ray_intersection_color(const Ray& r, size_t n_rec) const;

    SpectralColor calculate_punctual_light_contribution(const IntersectionObject& intersection) const;
    [[nodiscard]] std::array<double,2> get_random_pixel_coordinates(size_t x, size_t y) const;
    [[nodiscard]] Ray trace_ray(std::array<double,2> coordinates) const;
    [[nodiscard]] MatrixSC arrange_vector_into_color_matrix(std::vector<SpectralColor> colors) const;
  
public:
    explicit Render(Scene& s);
    ColorMap render_scene();

    [[nodiscard]] std::array<int,2> get_resolution() const;
};