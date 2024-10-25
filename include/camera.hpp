/**
 * @file camera.hpp
 * @brief Defines a camera with a screen.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the Camera class,
 * which represents a camera with a screen.
*/
#pragma once

#include <future>

#include "spatial_element/base.hpp"
#include "color/color_map.hpp"
#include "ray.hpp"
#include "geometry/geometry.hpp"
#include "light.hpp"

#include "threading/thread_pool.hpp"
#include "global_config/global_config.hpp"
#include "metrics/metrics.hpp"

/**
 * @brief Class that defines a Camera with a Screen
 */
class Camera
{
private:
    Base _screen_base;             // Base that defines the camera
    std::array<int,2> _resolution;
    /**
     * @brief Generate a ray with origin in the camera and direction
     * to the coordinates (X,y) inside the screen.
     * @param coordinates Coordinates of the pixel ((0,0) is the top-left
     * pixel of the screen)
     * @return A ray with origin in the camera and direction to the
     * coordinates (x,y) inside the screen.
     */
    Ray trace_ray(std::array<double,2> coordinates) const;

    /**
     * @brief Computes the color that a pixel must have.
     * @param x The x-position of the pixel
     * @param y The y-position of the pixel
     * @param k Number of rays to generate inside the pixel
     * @return The color that the pixel (x,y) must have.
     */
    SpectralColor compute_pixel_color(int x, int y, std::vector<Geometry*> objects,  std::vector<Light> lights) const;

    SpectralColor compute_random_pixel_color(int x, int y, std::vector<Geometry*> objects,  std::vector<Light> lights) const;

    /**
     * @brief Compute the coordinates of the pixel x,y in the camera
     * base
     * @param x The position in the width axis.
     * @param y The position in the height axis.
     * @return The coordinates of the pixel in the camera-base.
     */
    std::array<double,2> get_random_pixel_coordinates(int x, int y) const;

    std::vector<SpectralColor> paint_one_row(std::vector<Geometry*> objects,  std::vector<Light> lights, size_t row) const;

    SpectralColor compute_final_color(Intersection intersec, std::vector<Geometry*> objects, std::vector<Light> lights) const;

public:

    /**
     * @brief Constructor for the Camera class.
     * @param base The base that defines a camera.
     * @param width The width of the screen.
     * @param height The height of the screen.
     * @param distance The distance between the camera and the screen.
     * @throw std::invalid_argument if width, height or distance are not
     * positive numbers.
     */
    Camera(Base base, std::array<int,2> resolution);


    ColorMap paint_scene(std::vector<Geometry*> objects,  std::vector<Light> lights) const;

    SpatialElement* c_cam(const SpatialElement* s) const;

    std::array<int,2> get_resolution() const;

    /**
     * @brief Writes the information of a camera.
     * @param os The ostream.
     * @param c The camera.
     */
    friend std::ostream& operator<<(std::ostream& os, Camera c);


};
