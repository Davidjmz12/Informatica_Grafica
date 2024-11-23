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
    bool _initialized;

    [[nodiscard]] std::vector<Color> paint_k_pixels(std::array<size_t,2> start, size_t n_pixels) const;
    [[nodiscard]] Color compute_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] Color compute_random_pixel_color(size_t x, size_t y) const;
    [[nodiscard]] virtual Color compute_ray_color(const Ray& r) const = 0;
    [[nodiscard]] Color calculate_punctual_light_contribution(const IntersectionObject& intersection) const;

    [[nodiscard]] std::array<double,2> get_random_pixel_coordinates(size_t x, size_t y) const;
    [[nodiscard]] Ray trace_ray(std::array<double,2> coordinates) const;
    [[nodiscard]] MatrixSC arrange_vector_into_color_matrix(std::vector<Color> colors) const;
    
    virtual void init_render() = 0;
public:
    virtual ~Render() = default;
    explicit Render(Scene& s);
    [[nodiscard]] ColorMap render_scene();
    [[nodiscard]] std::array<int,2> get_resolution() const;
};