/**
 * @file planet.hpp
 * @brief Defines the Planet class.
 *
 * This file contains the definition of the Planet class, which represents
 * a planet in a 3D coordinate system.
*/

#pragma once

#include <iostream>

#include "base.hpp"
#include "linear_map.hpp"
#include "constants.hpp"

/**
 * @brief A class for represents a Planet.
 */
class Planet
{
    private:
        Point _center;       // Point: Center of the planet
        Point _ref_point;    // Point: Reference point
        Vector _axis;        // Vector: Axis that connects north and south pole 

        double _radius;           // The radius of the planet
        
        LinearMap _compute_point;

        Point parametric_point(float inclination, float azimut) const;

        LinearMap compute_azimut_rotation(const LinearMap* r) const;
        LinearMap compute_axis_rotation() const;
        
    public:

        Planet(Point center, Vector axis, Point ref_point);

        /**
        * @brief A method that computes the base_point reference
        * @param inclination The inclination of the station.
        * @param azimut The azimut of the station.
        * @return A tuple with the point and a basis 
        */
        Base base_point(double inclination, double azimut);

        /**
        * @brief A method checks if a point is in the planet.
        * @param p The point that is going to be checked.
        * @return True if the point is in the planet. False otherwise. 
        */
        bool point_in_planet(Point p);
};

/**
* @brief A method that computes if you can make a line between cities
*   without touching the planets.
* @param s1 The first planet
* @param az1 The azimut of the point in the first planet.
* @param inc1 The inclination of the point in the first planet.
* @param s2 The second planet
* @param az2 The azimut of the point in the second planet.
* @param inc2 The inclination of the point in the second planet.
* @return True if you cannot make a line between cities without touching the planets.
*/
bool collide(Planet s1, double az1, double inc1, Planet s2, double az2, double inc2);
