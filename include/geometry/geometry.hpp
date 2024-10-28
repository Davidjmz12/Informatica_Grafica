/**
 * @file geometry.hpp
 * @brief Defines a interface to define a geometry.
 * @authors Davidjmz12 DavidTizne
 * @date 08/10/2024
 *
 * This file contains the definition of the Geometry interface
 * that defines a geometry in R^3.
*/

#pragma once

#include "scene/intersection.hpp"
#include "properties/property.hpp"
#include "scene/ray.hpp"

/**
 * @class Geometry
 * @brief Abstract base class for geometric objects.
 * 
 * The Geometry class serves as an abstract base class for various geometric objects.
 * It provides a common interface for checking ray intersections and converting the geometry to a string.
 * 
 * @details
 * This class contains pure virtual functions that must be implemented by derived classes.
 * It also provides an overloaded << operator for easy output to an std::ostream.
 * 
 * @note
 * Derived classes must implement the intersect_with_ray and to_string methods.
 * 
 * @see Ray
 * @see Intersection
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
class Geometry
{
protected:
    Property _properties;
    
public:

    Geometry()
    {}

    Geometry(Property properties)
        : _properties(properties)
    {}
    
    /**
     * @brief Pure virtual function to check intersection with a ray.
     * 
     * This function determines whether a given ray intersects with the geometry.
     * If an intersection occurs, the details of the intersection are stored in the provided Intersection object.
     * 
     * @param r The ray to check for intersection.
     * @param intersection An Intersection object to store the details of the intersection if it occurs.
     * @return true if the ray intersects with the geometry, false otherwise.
     */
    virtual bool intersect_with_ray(const Ray& r, Intersection& intersection) const = 0; 


    /**
     * @brief Overloads the << operator to output the Geometry object to an output stream.
     * 
     * This friend function allows the Geometry object to be output to an std::ostream,
     * such as std::cout, for easy debugging and logging.
     * 
     * @param os The output stream to which the Geometry object will be written.
     * @param g The Geometry object to be written to the output stream.
     * @return std::ostream& The output stream after the Geometry object has been written to it.
     */
    friend std::ostream& operator<<(std::ostream& os, const Geometry& g);

    /**
     * @brief Pure virtual function to convert the geometry to a string.
     * 
     * This function returns a string representation of the geometry.
     * 
     * @return std::string The string representation of the geometry.
     */
    virtual std::string to_string() const = 0;

    Property get_properties() const
    {
        return this->_properties;
    }
};
