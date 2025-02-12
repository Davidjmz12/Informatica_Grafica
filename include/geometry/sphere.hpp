/**
 * @file sphere.hpp
 * @brief Defines the class Sphere.
 * @author Davidjmz12 DavidTizne
 *
 * This file contains the definition of the Sphere class,
 * which represents a sphere.
*/
#pragma once

#include "geometry/geometry.hpp"
#include "ellipsoid.hpp"

/**
 * @brief Defines a sphere in 3D
 */
class Sphere : public Ellipsoid
{
public:
    /**
     * @brief Constructor for the class Sphere.
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     * @param brdf The brdf of the sphere.
     * @throw std::invalid_argument if radius is zero.
     */
    Sphere(Point center, double radius, std::shared_ptr<BRDF> brdf);

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s);

    std::string to_string() const override;
};
