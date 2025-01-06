/**
 * @file area_light.hpp
 * @brief This file contains the definition of AreaLight class, which
 *  represents geometries that produce light.
 * @authors DavidTizne Davidjmz12
 * @date 03/11/2024
*/
#pragma once

#include "color/color.hpp"
#include "intersection/intersection_light.hpp"
#include "scene/ray.hpp"
#include "light/abstract_light.hpp"
#include "geometry/geometry.hpp"

/**
 * @brief Class for define a geometry that can produce light
 */
class AreaLight : public AbstractLight
{
private:
    std::shared_ptr<Geometry> _shape;       // The shape of the light
    Color _power;   // The luminance of the light

public:
    /**
     * @brief Constructor of the AreaLight class
     * @param shape The shape of the light
     * @param power The luminance of the light
     */
    AreaLight(std::shared_ptr<Geometry> shape, Color power);
    
    double luminance_max() const;

    /**
     * @brief Method for computing if a ray intersects with the AreaLight
     * @param r The ray
     * @param intersection[out] The information of the intersection
     * @return True if the ray instersects with the AreaLight. False otherwise.
     */
    bool intersect_with_ray(const Ray& r, IntersectionLight& intersection) const;

    /**
     * @brief Method for representing an AreaLight object with a string
     * @return A string with the information of the object.
     */
    std::string to_string() const;

    virtual Ray sample_ray() const override;
};
