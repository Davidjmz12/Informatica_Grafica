/**
 * @file cone.hpp
 * @author David Tizne, David Jiménez
 * @date 26-10
 * @brief File that describes a cone
 */
#pragma once

#include "geometry/disk.hpp"
#include "spatial_element/linear_map.hpp"

/**
 * @brief Class that describes a cone
 */
class Cone : public Geometry
{
private:
    Point _vertex;  // Vertex of the cone
    Vector _axe;    // Direction of the cone (from the vertex to the base)
    double _height; // Height
    double _radius; // Radius of the base
    Disk _base;     // Base

    LinearMap _centering;           // LinearMap for make counts easier
    LinearMap _centering_inverse;   // The inverse

public:
    /**
     * @brief Method that constructs a cone
     * @param vertex The vertex of the cone
     * @param axe Direction of the cone. From vertex to base
     * @param height Height
     * @param radius Radius of the base
     * @param properties Properties
     */
    Cone(Point vertex, Vector axe, double height, double radius, Property properties);

    /**
     * @brief Method that computes if a ray intersects with the cone
     * @param r The ray
     * @param intersection[out] The intersection information
     * @returns True if the ray intersects with the cone. False otherwise.
     *  If the ray intersects, the information is contained in the intersection
     *  object.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const override;

    /**
     * @brief Method that converts the information of the cone to a string
     * @return The string with the information of the cone
     */
    std::string to_string() const override;
};
