/**
 * @file ellipsoid.hpp
 * @brief Defines a ellipsoid.
 * @authors Davidjmz12 DavidTizne
 * @date 08/10/2024
 *
 * This file contains the definition of the Ellipsoid class, which represents
 * a ellipsoid in R^3.
*/

#pragma once

#include <stdexcept>
#include <tuple>
#include "geometry/geometry.hpp"



/**
 * @brief Defines a ellipsoid object in 3D
 */
class Ellipsoid : public Geometry
{
protected:
    double _a, _b, _c; // Parameters for defining the ellipsoid
    Point _center; // Center point

    /**
     * @brief Computes the normal vector of the ellipsoid in
     * the given point p.
     * @param p The point.
     * @throw std::runtime_error if the point is not in the ellipsoid.
     * @return The normal vector to the surface in the point p
     */
    Vector normal(Point p) const;

    /**
     * @brief Check if a point is in the ellipsoid
     * @param p The point that is going to be checked.
     * @return True if the point is in the ellipsoid. False otherwise.
     */
    bool is_in_ellipsoid(Point p) const;

public:

    /**
     * @brief Constructor for the Ellipsoid class.
     * @param a The x-factor.
     * @param b The y-factor.
     * @param c The z-factor.
     * @param center The center.
     * @throw std::invalid_argument if some factors are zero.
     */
    Ellipsoid(double a, double b, double c, Point center, Property properties);

    /**
     * @brief Computes if the ellipsoid intersects with a ray and stores
     * the instersection information.
     * @param r The ray.
     * @param intersection The object in which the information is going
     * to be stored.
     * @return True if there is an intersection. False otherwise.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const override;

    friend std::ostream& operator<<(std::ostream& os, const Ellipsoid& e);

    std::string to_string() const override;
};
