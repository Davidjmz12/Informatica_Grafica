/**
 * @file sphere.hpp
 * @brief Defines the Sphere class.
 *
 * This file contains the definition of the Sphere class, which represents
 * a sphere in a 3D coordinate system.
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "geometric.hpp"
#include "base.hpp"

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

#endif