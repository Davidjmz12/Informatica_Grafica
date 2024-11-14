#pragma once

#include "scene/scene.hpp"
#include "global_config/global_config.hpp"
#include "threading/thread_pool.hpp"
#include "color/color_map.hpp"
#include "intersection/intersection_object.hpp"

class Render {
protected:
    Scene& _scene;
    GlobalConf* _gc;
    ThreadPool _pool;

    [[nodiscard]] std::vector<SpectralColor> paint_k_pixels(std::array<size_t,2> start, size_t n_pixels) const;
    [[nodiscard]] SpectralColor compute_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] SpectralColor compute_random_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] virtual SpectralColor compute_ray_color(const Ray& r) const = 0;

    [[nodiscard]] std::array<double,2> get_random_pixel_coordinates(size_t x, size_t y) const;
    [[nodiscard]] Ray trace_ray(std::array<double,2> coordinates) const;
    [[nodiscard]] MatrixSC arrange_vector_into_color_matrix(std::vector<SpectralColor> colors) const;
  
public:
    virtual ~Render() = default;

    explicit Render(Scene& s);
    ColorMap render_scene() ;
    [[nodiscard]] std::array<int,2> get_resolution() const;
};