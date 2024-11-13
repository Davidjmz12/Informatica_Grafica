/**
 * @file camera.hpp
 * @brief Defines a camera with a screen.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the Camera class,
 * which represents a camera with a screen.
*/
#pragma once

#include "spatial_element/base.hpp"

/**
 * @brief Class that defines a Camera with a Screen
 */
class Camera
{
private:
    Base _screen_base;             // Base that defines the camera
    std::array<int,2> _resolution;
    
public:

    /**
     * @brief Constructor for the Camera class.
     * @param base The base that defines a camera.
     * @param resolution The resolution of the camera.
     * @throw std::invalid_argument if width, height or distance are not
     * positive numbers.
     */
    Camera(Base base, std::array<int,2> resolution);

    SpatialElement* transform_to_canonical(const SpatialElement* s) const;

    [[nodiscard]] std::array<int,2> get_resolution() const;

    [[nodiscard]] Base get_screen_base() const;

    /**
     * @brief Writes the information of a camera.
     * @param os The ostream.
     * @param c The camera.
     */
    friend std::ostream& operator<<(std::ostream& os, Camera c);

    std::string to_string();

};
