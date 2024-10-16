/**
 * @file triangle_mesh.hpp
 * @brief Defines the class TriangleMesh.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the TriangleMesh class,
 * which represents a 3D mesh composed of triangles.
*/
#pragma once

#include <vector>

#include "geometry/geometry.hpp"
#include "geometry/triangle.hpp"


/**
 * @class TriangleMesh
 * @brief Represents a 3D geometric mesh composed of triangles.
 * 
 * The TriangleMesh class models a 3D mesh defined by a collection of triangles.
 * It provides methods to compute intersections with rays and to represent the mesh as a string.
 * 
 * @details
 * The triangle mesh is defined by:
 * - A vector of triangles (_triangles) which represents the individual triangles that make up the mesh.
 * 
 * The class provides methods to:
 * - Compute the intersection of a ray with the triangle mesh.
 * - Find the closest intersection point from a list of intersections.
 * - Represent the triangle mesh as a string.
 * 
 * @note This class inherits from the Geometry class.
 * 
 * @section Example of a TriangleMesh:
 * @code
 * std::vector<Triangle> triangles = {Triangle(Point(0,0,0), Point(1,0,0), Point(0,1,0))};
 * TriangleMesh mesh(triangles);
 * @endcode
 *
 * @see Geometry, Triangle, Ray, Intersection
 * 
 * @version
 * 1.0
 * 
 * @date
 * 2024-2025
 * 
 */
class TriangleMesh : public Geometry
{
private:
    std::vector<Triangle> _triangles; ///< The triangles that make up the mesh
    Intersection min_distance(std::vector<Intersection> intersections) const; ///< Find the closest intersection point from a list of intersections
public:

    /**
     * @brief Default constructor for the TriangleMesh class.
     */
    TriangleMesh();

    /**
     * @brief Constructor for the TriangleMesh class.
     * @param triangles The triangles that make up the mesh.
     */
    TriangleMesh(std::vector<Triangle> triangles, Property properties);

    /**
     * @brief Checks if a given ray intersects with the triangle mesh.
     * 
     * This function determines whether a ray intersects with the triangle mesh
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the mesh.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the triangle mesh, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;


    /**
     * @brief Overloads the << operator to output the details of a TriangleMesh object.
     * @param os The ostream.
     * @param tm The TriangleMesh object.
     * @return The ostream with the details of the TriangleMesh object.
     */
    friend std::ostream& operator<<(std::ostream& os, const TriangleMesh& tm);

    /**
     * @brief Method that returns a string representation of the triangle mesh.
     * @return A string representation of the triangle mesh.
     */
    std::string to_string() const;
};