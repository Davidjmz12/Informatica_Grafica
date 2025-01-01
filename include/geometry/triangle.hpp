/**
 * @file triangle.hpp
 * @brief Defines the class Triangle.
 * @author Davidjmz12 DavidTizne
 *
 * This file contains the definition of the Triangle class,
 * which represents a 3D triangle.
*/

#pragma once

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"


/**
 * @class Triangle
 * @brief Represents a single triangle in 3D space.
 * 
 * The Triangle class models a 3D triangle defined by three vertices.
 * It provides methods to compute intersections with rays and to represent the triangle as a string.
 * 
 * @details
 * The triangle is defined by:
 * - Three points (vertices) which represent the corners of the triangle.
 * 
 * The class provides methods to:
 * - Compute the intersection of a ray with the triangle.
 * - Represent the triangle as a string.
 * 
 * @note This class can be used as a building block for more complex geometric structures like meshes.
 * 
 * @section Example of a Triangle:
 * @code
 * Triangle triangle(Point(0,0,0), Point(1,0,0), Point(0,1,0));
 * @endcode
 *
 * @see Point, Ray, Intersection
 * 
 * @version
 * 1.0
 * 
 * @date
 * 2024-2025
 * 
 */
class Triangle final : public Geometry
{
private:
    std::shared_ptr<Point> _v0; ///< The first vertex of the triangle
    std::shared_ptr<Point> _v1; ///< The second vertex of the triangle
    std::shared_ptr<Point> _v2; ///< The third vertex of the triangle
    BoundingBox __bb; ///< The bounding box of the triangle
    
    /**
     * @brief Checks if a given point is inside the triangle.
     * 
     * This function determines whether a specified point lies within the boundaries
     * of the triangle. It uses geometric calculations to ascertain the position of
     * the point relative to the triangle's vertices. The point must lie within the
     * plane containing the triangle.
     * 
     * @param p The point to be checked that is inside the plane containing the triangle.
     * @return true if the point is inside the triangle, false otherwise.
     */
    [[nodiscard]] bool point_inside_triangle(const Point& p) const;

public:

    /**
     * @brief Constructor for the Triangle class.
     * @param v0 The first vertex of the triangle.
     * @param v1 The second vertex of the triangle.
     * @param v2 The third vertex of the triangle.
     * @throw std::invalid_argument if the vertices are not different or if they are linearly dependent.
     */
    Triangle(std::shared_ptr<Point> v0, std::shared_ptr<Point> v1, std::shared_ptr<Point> v2, std::shared_ptr<BRDF> brdf);

    BoundingBox get_bounding_box() const override;

    /**
     * @brief Computes the intersection of a ray with the triangle.
     * 
     * This function determines if a given ray intersects with the triangle
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the triangle.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the triangle, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const;

    /**
     * @brief Overloads the [] operator to access the vertices of the triangle.
     * 
     * This operator allows the vertices of the triangle to be accessed using an index.
     * The index must be in the range [0, 2] to access the three vertices.
     * 
     * @param i The index of the vertex to access.
     * @return The vertex at the specified index.
     */
    Point operator[](int i) const;

    /**
     * @brief Overloads the << operator to output the details of a Triangle object.
     * 
     * This friend function allows the Triangle object to be output to an ostream,
     * such as std::cout, in a formatted manner.
     * 
     * @param os The output stream to which the Triangle object will be written.
     * @param t The Triangle object to be output.
     * @return std::ostream& The output stream after the Triangle object has been written to it.
     */
    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);

    /**
     * @brief Converts the triangle to a string.
     * @return The string representation of the triangle.
     */
    [[nodiscard]] std::string to_string() const;

};