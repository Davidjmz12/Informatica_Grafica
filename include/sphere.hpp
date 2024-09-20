/**
 * @file sphere.hpp
 * @brief Defines the Sphere class.
 *
 * This file contains the definition of the Sphere class, which represents
 * a sphere in a 3D coordinate system.
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>

#include "base.hpp"
#include "linear_map.hpp"

/**
 * @brief A class for represents a Sphere.
 */
class Sphere
{
    private:
        Geometric center;       // Point: Center of the sphere
        Geometric ref_point;    // Point: Reference point
        Geometric axis;         // Vector: Axis that connects north and south pole 

        float radius;           // The radius of the sphere
        

    public:

        Sphere(Geometric center, Geometric axis, Geometric ref_point);

        /**
        * @brief A method that computes the base_point reference
        * @param inclination The inclination of the station.
        * @param azimut The azimut of the station.
        * @return A tuple with the point and a basis 
        */
        Base base_point(float inclination, float azimut);

        /**
        * @brief A method checks if a point is in the sphere.
        * @param p The point that is going to be checked.
        * @return True if the point is in the sphere. False otherwise. 
        */
        bool point_in_sphere(Geometric p);
};

/**
* @brief A method that computes if you can make a line between cities
*   without touching the spheres.
* @param s1 The first sphere
* @param az1 The azimut of the point in the first sphere.
* @param inc1 The inclination of the point in the first sphere.
* @param s2 The second sphere
* @param az2 The azimut of the point in the second sphere.
* @param inc2 The inclination of the point in the second sphere.
* @return True if you can make a line between cities without touching the spheres.
*/
bool collide(Sphere s1, float az1, float inc1, Sphere s2, float az2, float inc2);

#endif