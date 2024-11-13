#pragma once

#include <array>

#include "geometry/mesh.hpp"
#include "geometry/face.hpp"

/**
 * @class Box
 * @brief Represents a 3D box geometry.
 * 
 * The Box class inherits from the Geometry class and represents a 3D box using a face mesh.
 * It provides methods to construct the box and check for ray intersections.
 *
 *
 * @section SeeAlso
 * Geometry, Mesh, Ray, IntersectionObject
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
class Box final : public Geometry
{
private:
    Mesh _mesh; ///< The mesh that represents the box
    BoundingBox _bounding_box; ///< The bounding box of the box
public:

    /**
     * @brief Constructor for the Box class.
     * @param center The center of the box.
     * @param axis The axis of the box.
     * @param properties The properties of the box.
     * @throw std::invalid_argument if the sides are not positive, the axis are not normalized or the axis are not a R^3 basis.
     */
    Box(const Point& center, std::array<Vector,3> axis, const Property& properties);

    /**
     * @brief Method that returns the bounding box of the box.
     * @return The bounding box of the box.
     */
    [[nodiscard]] BoundingBox get_bounding_box() const override;
    
    /**
     * @brief Method that checks if a ray intersects with the box.
     * @param r The ray that is going to be checked.
     * @param intersection The intersection with the ray.
     * @return True if the ray intersects with the box. False otherwise.
     *         If the ray intersects, the intersection is stored in the intersection parameter.
     *         If not, the intersection parameter can be modified with a non-expected value.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const override;

    /**
     * @brief Overloads the << operator to output the details of a Box object.
     * 
     * This friend function allows the Box object to be output to an ostream,
     * such as 'std::cout' in a formatted manner.
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
    [[nodiscard]] std::string to_string() const override;
};