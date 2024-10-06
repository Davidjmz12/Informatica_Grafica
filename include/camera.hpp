/**
 * @file camera.hpp
 * @brief Defines a camera with a screen.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the Camera class,
 * which represents a camera with a screen.
*/
#pragma once

#include "base.hpp"
#include "color_map.hpp"
#include "ray.hpp"

/**
 * @brief Class that defines a Camera with a Screen
 */
class Camera
{
private:
    Base _base;             // Base that defines the camera
    double _width, _height;  // Dimensions of the screen
    double _distance;        // Distance to the screen
    ColorMap _screen;       // Screen

    /**
     * @brief Generate a ray with origin in the camera and direction
     * to the coordinates (X,y) inside the screen.
     * @param x The x-axis coordinates.
     * @param y The y-axis coordinates.
     * @return A ray with origin in the camera and direction to the
     * coordinates (x,y) inside the screen.
     */
    Ray trace_ray(double x, double y) const;

    /**
     * @brief Computes the color that a pixel must have.
     * @param x The x-position of the pixel
     * @param y The y-position of the pixel
     * @param k Number of rays to generate inside the pixel
     * @return The color that the pixel (x,y) must have.
     */
    Color compute_pixel_color(int x, int y, int k) const;

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
    Camera(Base base, double width, double height, double distance);

    /**
     * @brief Writes the information of a camera.
     * @param os The ostream.
     * @param c The camera.
     */
    friend std::ostream& operator<<(std::ostream& os, Camera c);
};
