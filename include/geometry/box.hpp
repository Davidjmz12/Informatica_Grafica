/**
 * @file box.hpp
 * @brief Defines a R^3 box.
 * @authors Davidjmz12 DavidTizne
 * @date 08/10/2024
 *
 * This file contains the definition of the Box class, which represents
 * a box in R^3.
*/

#pragma once

#include <array>

#include "geometry/triangle_mesh.hpp"

/**
 * @class Box
 * @brief Represents a 3D box geometry.
 * 
 * The Box class inherits from the Geometry class and represents a 3D box using a triangular mesh.
 * It provides methods to construct the box and check for ray intersections.
 * 
 * @note The box is defined by its center, half side lengths, and axis.
 * 
 * @section Example of a Box centered at the origin with sides of length 2 and axis aligned with the coordinate axes:
 * @code
 * Point center(0.0, 0.0, 0.0);
 * std::array<double, 3> sides = {1.0, 1.0, 1.0};
 * std::array<Vector, 3> axis = {Vector(1,0,0), Vector(0,1,0), Vector(0,0,1)};
 * Box box(center, sides, axis);
 * @endcode
 * 
 * @section SeeAlso
 * Geometry, TriangleMesh, Ray, Intersection
 * 
 * @author
 * Davidjmz12 
 * DavidTizne
 * 
 * @version
 * 1.0
 * 
 * @date
 * 2024-2025
 */
class Box : public Geometry
{
private:
    TriangleMesh _mesh; ///< The mesh that represents the box
public:

    /**
     * @brief Constructor for the Box class.
     * @param center The center of the box.
     * @param sides The half sides length of the box.
     * @param axis The axis of the box.
     * @throw std::invalid_argument if the sides are not positive, the axis are not normalized or the axis are not a R^3 basis.
     */
    Box(Point center, std::array<double,3> sides, std::array<Vector,3> axis);

    /**
     * @brief Method that checks if a ray intersects with the box.
     * @param r The ray that is going to be checked.
     * @param intersection The intersection with the ray.
     * @return True if the ray intersects with the box. False otherwise.
     *         If the ray intersects, the intersection is stored in the intersection parameter.
     *         If not, the intersection parameter can be modified with a non-expected value.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

    /**
     * @brief Overloads the << operator to output the details of a Box object.
     * 
     * This friend function allows the Box object to be output to an ostream,
     * such as std::cout, in a formatted manner.
     * 
     * @param os The output stream to which the Box object will be written.
     * @param b The Box object to be output.
     * @return std::ostream& The output stream after the Box object has been written to it.
     */
    friend std::ostream& operator<<(std::ostream& os, const Box& b);

    /**
     * @brief Method that returns a string representation of the box.
     * @return A string representation of the box.
     */
    std::string to_string() const override;
};