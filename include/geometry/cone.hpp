/**
 * @file cone.hpp
 * @author David Tizne, David Jiménez
 * @date 26-10
 * @brief File that describes a cone
 */
#pragma once

#include "geometry/disk.hpp"

/**
 * @brief Class that describes a cone
 */
class Cone : public Geometry
{
private:
    Point _center;  // Center of the cone
    Vector _axe;    // Direction of the cone (from the vertex to the base)
    double _height; // Height
    double _radius; // Radius of the base
    Disk _base;     // Base

    bool intersection_in_a_point(const Ray& r, double distance, IntersectionObject& intersection) const;
    bool intersect_with_cone(const Ray& r, IntersectionObject& intersection) const;
public:

    BoundingBox get_bounding_box() const;

    /**
     * @brief Method that constructs a cone
     * @param center The center of the cone
     * @param axe Direction of the cone. From vertex to base
     * @param radius Radius of the base
     * @param brdf brdf
     */
    Cone(Point center, Vector axe, double radius, std::shared_ptr<BRDF> brdf);

    /**
     * @brief Method that computes if a ray intersects with the cone
     * @param r The ray
     * @param intersection[out] The intersection information
     * @returns True if the ray intersects with the cone. False otherwise.
     *  If the ray intersects, the information is contained in the intersection
     *  object.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const override;

    /**
     * @brief Method that converts the information of the cone to a string
     * @return The string with the information of the cone
     */
    std::string to_string() const override;
};