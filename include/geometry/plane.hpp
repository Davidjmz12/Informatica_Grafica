/**
 * @file plane.hpp
 * @brief Defines the class Plane.
 * @author Davidjmz12 DavidTizne
 *
 * This file contains the definition of the Plane class,
 * which represents a 3D plane.
*/

#pragma once

#include "geometry/geometry.hpp"

/**
 * @class Plane
 * @brief Represents a geometric plane in 3D space.
 * 
 * The Plane class defines a plane using a point on the plane and a normal vector.
 * It provides methods for constructing a plane, retrieving its properties, and checking for ray intersections.
 * 
 * @details
 * This class inherits from the Geometry class and implements its pure virtual functions.
 * It allows for the creation of a plane from either a point and a normal vector or from three points.
 * 
 * @note
 * The normal vector should be a unit vector for accurate intersection calculations.
 * 
 * @see Geometry
 * @see Ray
 * @see Intersection
 * 
 * @authors
 * Davidjmz12
 * DavidTizne
 * 
 * @version
 * 1.0
 * 
 * @date
 * 2024-2025
 */
class Plane : public Geometry
{
private:
    Vector _normal; ///< The normal vector of the plane.
    double _distance;   ///< A point on the plane.
    
public:
    /**
     * @brief Constructs a plane from a point and a normal vector.
     * @param point A point on the plane.
     * @param normal The normal vector of the plane.
     */
    Plane(Point point, Vector normal, Property properties);

    Plane(Vector normal, double distance, Property properties);

    BoundingBox get_bounding_box() const override;

    /**
     * @brief Constructs a plane from three points.
     * @param p1 The first point.
     * @param p2 The second point.
     * @param p3 The third point.
     */
    Plane(Point p1, Point p2, Point p3, Property properties);


    double get_distance() const;

    /**
     * @brief Gets the normal vector of the plane.
     * @return The normal vector of the plane.
     */
    Vector get_normal() const;

    /**
     * @brief Checks if a ray intersects with the plane.
     * @param r The ray to check for intersection.
     * @param intersection The intersection details if an intersection occurs.
     * @return True if the ray intersects with the plane, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

    /**
     * @brief Overloads the << operator to output the details of a Plane object.
     * 
     * This friend function allows the Plane object to be output to an ostream,
     * such as std::cout, in a formatted manner.
     * 
     * @param os The output stream to which the Plane object will be written.
     * @param p The Plane object to be output.
     * @return std::ostream& The output stream after the Plane object has been written to it.
     */
    friend std::ostream& operator<<(std::ostream& os, const Plane& p);

    /**
     * @brief Converts the plane to a string.
     * 
     * This function returns a string representation of the plane.
     * 
     * @return std::string The string representation of the plane.
     */
    std::string to_string() const override;
};
