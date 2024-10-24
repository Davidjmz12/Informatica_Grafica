/**
 * @file disk.hpp
 * @brief Defines a R^3 disk.
 * @authors Davidjmz12 DavidTizne
 * @date 08/10/2024
 *
 * This file contains the definition of the Disk class, which represents
 * a disk in R^3.
*/

#pragma once 

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

/**
 * @class Disk
 * @brief Represents a disk geometry in 3D space.
 * 
 * The Disk class inherits from the Geometry class and represents a disk defined by a plane and a radius.
 * 
 * @details
 * The disk is defined by a center point, a normal vector to the plane of the disk, and a radius.
 * It provides functionality to check for intersections with rays.
 * 
 * @note The disk lies on the plane defined by the center point and the normal vector.
 * 
 * @sa Geometry
 * 
 * @section Example of a Disk centered at the origin with radius 1 and normal vector (0,0,1):
 * @code
 * Point center(0.0, 0.0, 0.0);
 * Vector normal(0.0, 0.0, 1.0);
 * double radius = 1.0;
 * Disk disk(center, normal, radius);
 * @endcode
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
 * 
 */
class Disk: public Geometry
{
private:
    Plane _plane;
    Point _center;
    Vector _normal;
    double _radius; ///< The radius of the disk
public:

    /**
     * @brief Constructor for the Disk class.
     * @param center The center of the disk.
     * @param normal The normal vector to the plane of the disk.
     * @param radius The radius of the disk.
     */
    Disk(Point center, Vector normal, double radius, Property properties);

    BoundingBox get_bounding_box() const override;

    /**
     * @brief Checks if a given ray intersects with the disk.
     * 
     * This function determines whether a ray intersects with the disk
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the disk.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the disk, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;


    /**
     * @brief Overloads the << operator to output the details of a Disk object.
     * 
     * This friend function allows the Disk object to be output to an 
     * output stream (such as std::cout) in a formatted manner.
     * 
     * @param os The output stream to which the Disk object will be written.
     * @param d The Disk object to be output.
     * @return A reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Disk& d);

    /**
     * @brief Converts the disk to a string.
     * 
     * This function returns a string representation of the disk.
     * 
     * @return The string representation of the disk.
     */
    std::string to_string() const override;

};
