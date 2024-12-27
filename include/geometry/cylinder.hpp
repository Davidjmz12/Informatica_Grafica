/**
 * @file cylinder.hpp
 * @brief Defines a R^3 cylinder.
 * @authors Davidjmz12 DavidTizne
 * @date 08/10/2024
 *
 * This file contains the definition of the Cylinder class, which represents
 * a cylinder in R^3.
*/


#include "geometry/geometry.hpp"
#include "geometry/disk.hpp"


/**
 * @class Cylinder
 * @brief Represents a 3D geometric cylinder.
 * 
 * The Cylinder class models a 3D cylinder defined by a center point, radius, axis, and height.
 * It provides methods to compute intersections with rays and to represent the cylinder as a string.
 * 
 * @details
 * The cylinder is defined by:
 * - A center point (_center) which is the center of the bottom base.
 * - A radius (_radius) which is the radius of the cylinder.
 * - An axis (_axis) which is the axis of the cylinder.
 * - A height (_height) which is the height of the cylinder.
 * - Top and bottom disks (_top, _bottom) which represent the top and bottom bases of the cylinder.
 * 
 * The class provides methods to:
 * - Compute the intersection of a ray with an infinite cylinder.
 * - Check if a ray intersects with a finite cylinder.
 * - Compute the intersection of a ray with a point in the cylinder.
 * - Represent the cylinder as a string.
 * 
 * @note This class inherits from the Geometry class.
 * 
 * @section Example of a Cylinder centered at the origin with radius 1, axis (1/4,1/3,0.3), and height 2:
 * @code
 * Point center(0.0, 0.0, 0.0);
 * double radius = 1.0;
 * Vector axis(1/4.0, 1/3.0, 0.3);
 * Cylinder cylinder(center, radius, axis);
 * @endcode
 *
 * @see Geometry
 * @section SeeAlso
 * Geometry, Disk, Ray, Intersection
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
class Cylinder: public Geometry
{
private:
    Point _center; ///< The center of the bottom base of the cylinder
    double _radius; ///< The radius of the cylinder
    Vector _axis; ///< The axis of the cylinder
    double _height; ///< The height of the cylinder
    Disk _top, _bottom; ///< The top and bottom disks of the cylinder


    BoundingBox get_bounding_box() const override;

    /**
     * @brief Computes the intersection of a ray with an infinite cylinder.
     * 
     * This function determines if a given ray intersects with an infinite cylinder
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the infinite cylinder.
     * @param intersection A reference to an Intersection object where the details
     *                     of the intersection will be stored if an intersection occurs.
     * @return true if the ray intersects with the infinite cylinder, false otherwise.
     */
    bool intersect_with_ray_infinite_cylinder(const Ray& r, IntersectionObject& intersection) const;

    /**
     * @brief Checks if a given ray intersects with the base of the cylinder.
     * 
     * This function determines whether a ray intersects with the base of the cylinder
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the base.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the base, false otherwise.
     */
    bool intersect_with_base(const Ray& r, IntersectionObject& intersection) const;

    /**
     * @brief Checks if a given ray intersects with a finite cylinder.
     * 
     * This function determines whether a ray intersects with a finite cylinder
     * and, if so, provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the cylinder.
     * @param intersection An output parameter that will contain details about the intersection if one occurs.
     * @return true if the ray intersects with the finite cylinder, false otherwise.
     */
    bool intersect_with_ray_finite_cylinder(const Ray& r, IntersectionObject& intersection) const;

    /**
     * @brief Computes the intersection of a ray with a point in the cylinder.
     * 
     * This function computes the intersection of a ray with a point in the cylinder
     * and provides details about the intersection.
     * 
     * @param r The ray to test for intersection with the point.
     * @param distance The distance from the origin of the ray to the point of intersection.
     *                 This distance determines the point of intersection.
     * @return An Intersection object containing details about the intersection.
     */
    IntersectionObject intersection_in_a_point(const Ray& r, double distance) const;

public:

    /**
     * @brief Constructor for the Cylinder class.
     * 
     * This constructor creates a Cylinder object with the specified center, radius, axis, and height.
     * 
     * @param center The center of the bottom base of the cylinder.
     * @param radius The radius of the cylinder.
     * @param axis The axis of the cylinder. The norm of the axis determines the height of the cylinder.
     * @throw std::invalid_argument if the radius is not positive or the axis is the zero vector.
     * 
     */
    Cylinder(Point center, double radius, Vector axis, std::shared_ptr<Property> properties);
    
    /**
     * @brief Checks if a given ray intersects with the cylinder.
     * 
     * This function determines whether the provided ray intersects with the cylinder
     * and, if so, updates the intersection details.
     * 
     * @param r The ray to check for intersection.
     * @param intersection The intersection details to be updated if an intersection occurs.
     * @return true if the ray intersects with the cylinder, false otherwise.
     */
    bool intersect_with_ray(const Ray& r, IntersectionObject& intersection) const;


    /**
     * @brief Converts the cylinder object to its string representation.
     * 
     * @return A string that represents the cylinder object.
     */
    std::string to_string() const;
};