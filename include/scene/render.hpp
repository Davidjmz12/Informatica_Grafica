#pragma once

#include "scene/scene.hpp"
#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "color/color_map.hpp"

class Render {
private:
    Scene _scene;
    GlobalConf* _gc;
    ThreadPool _pool;

    std::vector<SpectralColor> paint_k_pixels(std::array<size_t,2> start, size_t n_pixels) const;
    SpectralColor compute_pixel_color(int x, int y) const;
    SpectralColor compute_random_pixel_color(int x, int y) const;
    SpectralColor compute_ray_intersection_color(Ray r, size_t n_rec) const;
    

    SpectralColor calculate_total_light(IntersectionObject& intersection) const;
    std::array<double,2> get_random_pixel_coordinates(int x, int y) const;
    Ray trace_ray(std::array<double,2> coordinates) const;
    MatrixSC arrange_vector_into_color_matrix(std::vector<SpectralColor> colors) const;
  
public:
    Render(Scene s);
    ColorMap render_scene();

    std::array<int,2> get_resolution() const;
};