/**
 * @file mesh.hpp
 * @brief Defines the class Mesh.
 * @author Davidjm12
 *
 * This file contains the definition of the Mesh class,
 * which represents a 3D mesh composed of different geometries.
*/
#pragma once

#include "geometry/geometry.hpp"
#include "geometry/bounding_box.hpp"
#include "geometry/kd-trees/kd-tree.hpp"

#include "global_config/global_config.hpp"

/**
 * @class Mesh
 * @brief Represents a 3D geometric mesh composed of geometries.
 * 
 * The Mesh class models a 3D mesh defined by a collection of geometries.
 * It provides methods to compute intersections with rays and to represent the mesh as a string.
 * 
 * @details
 * The geometries mesh is defined by:
 * - A vector of geometries (_elements) which represents the individual geometries that make up the mesh.
 * 
 * The class provides methods to:
 * - Compute the intersection of a ray with the mesh.
 * - Find the closest intersection point from a list of intersections.
 * - Represent the mesh as a string.
 * 
 * @note This class inherits from the Geometry class.
 *
 * @see Geometry, Ray, IntersectionObject
 * 
 * @version
 * 1.0
 * 
 * @date
 * 2024-2025
 * 
 */
class Mesh final: public Geometry
{
protected:
    KDTree _kd_tree;
public:

    Mesh();

    /**
     * @brief Constructor for the Mesh class.
     * @param elements The geometries that make up the mesh.
     */
    Mesh(VectorGeometries elements);

    BoundingBox get_bounding_box() const override;

    /**
     * @brief Checks if a given ray intersects with the mesh.
     * 
     * This function determines whether a ray intersects with the mesh
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the mesh.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the mesh, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const;


    /**
     * @brief Overloads the << operator to output the details of a Mesh object.
     * @param os The ostream.
     * @param m The Mesh object.
     * @return The ostream with the details of the Mesh object.
     */
    friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

    /**
     * @brief Method that returns a string representation of the mesh.
     * @return A string representation of the mesh.
     */
    std::string to_string() const;
};