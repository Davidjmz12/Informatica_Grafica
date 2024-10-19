#pragma once
#include <iostream>

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"


/**
 * @class Face
 * @brief Represents a face geometry in 3D space.
 * 
 * The Face class inherits from the Geometry class and represents a polygonal face defined by a normal and two vector perpendicular
 * to the normal vector.
 * 
 * @details
 * The face is defined by a a normal vector to the plane of the face and two vectors that define the boundary of the face.
 * It provides functionality to check for intersections with rays and to convert the face to a string representation.
 * 
 * @note The face lies on the plane defined by a normal.
 * 
 * @sa Geometry
 * 
 * @section Example of a Face defined by three vertices:
 * @code
 * Vector normal(0.0, 0.0, 1.0);
 * Vector u(1.0, 0.0, 0.0);
 * Vector v(0.0, 1.0, 0.0);
 * Point point(0.0, 0.0, 0.0);
 * Face face(normal, u, v, point);
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
class Face: public Geometry
{
private:
    Vector _normal; ///> Normal vector to the face
    Vector _u,_v; ///> Two vectors that define the plane
    Point _point; ///> Point in the plane
    std::array<double,2> _sizes; ///> Sizes of the face
    
public:

    /**
     * @brief Constructor for the Face class.
     * @param normal The normal vector to the plane of the face.
     * @param u The first vector that defines the boundary of the face.
     * @param v The second vector that defines the boundary of the face.
     */
    Face(Vector normal, Vector u, Vector v, Point point, Property properties);


    /**
     * @brief Computes if the face intersects with a ray and stores
     * the instersection information.
     * @param r The ray.
     * @param intersection The object in which the information is going
     * to be stored.
     * @return True if the face intersects with the ray. False otherwise.
     */
    bool intersect_with_ray(const Ray& r, Intersection& intersection) const override;


    /**
     * @brief Writes the information of a face.
     * @param os The output stream.
     * @param f The face to write.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Face& f);


    /**
     * @brief Converts the face to a string representation.
     * @return The string representation of the face.
     */
    std::string to_string() const override;

};