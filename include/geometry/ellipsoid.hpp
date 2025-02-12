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
    double _a, _b, _c; ///> Parameters for defining the ellipsoid
    Point _center; ///> Center point

    /**
     * @brief Computes the normal vector of the ellipsoid in
     * the given point p.
     * @param p The point.
     * @throw std::runtime_error if the point is not in the ellipsoid.
     * @return The normal vector to the surface in the point p
     */
    [[nodiscard]] Vector normal(const Point& p) const;

public:

    /**
     * @brief Constructor for the Ellipsoid class.
     * @param a The x-factor.
     * @param b The y-factor.
     * @param c The z-factor.
     * @param center The center.
     * @param brdf The brdf of the ellipsoid.
     * @throw std::invalid_argument if some factors are zero.
     */
    Ellipsoid(double a, double b, double c, Point center, std::shared_ptr<BRDF> brdf);

    std::pair<double, double> get_u_v_coordinates(const Point& p) const override;
    
    [[nodiscard]] BoundingBox get_bounding_box() const override;

    /**
     * @brief Computes if the ellipsoid intersects with a ray and stores
     * the instersection information.
     * @param r The ray.
     * @param intersection The object in which the information is going
     * to be stored.
     * @return True if there is an intersection. False otherwise.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const override;

    Ray sample_ray() const override;

    friend std::ostream& operator<<(std::ostream& os, const Ellipsoid& e);

    [[nodiscard]] std::string to_string() const override;
};
