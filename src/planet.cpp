/**
 * @file planet.cpp
 * @brief Implementation of the planet header.
 * @authors DavidJimenez DavidTizne
 * @date 18/09/2024
 * @see planet.hpp for more information.
 * This file contains the implementation of planet in R^3.
*/

#include <math.h>

#include "planet.hpp"

#include "constants.hpp"


bool collide(Planet s1, double az1, double inc1, Planet s2, double az2, double inc2)
{
    Base b1 = s1.base_point(inc1,az1); 
    Base b2 = s2.base_point(inc2,az2);
    Geometric coord_b1 = b1.coord_from_canonical(b2.center);
    Geometric coord_b2 = b2.coord_from_canonical(b1.center);
    
    return leF(coord_b1[2],0) || leF(coord_b2[2],0);
}


Planet::Planet(Geometric center, Geometric axis, Geometric ref_point)
    : center(center), ref_point(ref_point), axis(axis), radius(axis.norm())
{
    // Check if the parameters are correct
    if (center.is_vector() || axis.is_point() || ref_point.is_vector())
        throw std::invalid_argument("Center and ref_point must be points. Axis must be a vector.");

    // Check if the ref_point is in the planet
    if (!this->point_in_planet(ref_point))
        throw std::invalid_argument("Error: The ref_point is not in the planet.");
}

Base Planet::base_point(double inclination, double azimut)
{
    //Compute the point
    LinearMap r1 = LinearMap::rotation(this->axis,azimut);
    Geometric v1 = r1*(this->ref_point-this->center);
    Geometric axis_second_rotation =  this->axis.cross(v1);

    double angle_ref_axis = acos(this->axis.normalize().dot((this->ref_point-this->center).normalize()));

    LinearMap r2 = LinearMap::rotation(axis_second_rotation,inclination - angle_ref_axis);

    Geometric point = r2*v1 + this->center;

    //Compute the axis
    Geometric normal = (point-this->center).normalize();
    Geometric tangent_long = this->axis.cross(normal).normalize();
    Geometric tangent_lat = normal.cross(tangent_long);

    return Base(point, tangent_long, tangent_lat, normal);
}

bool Planet::point_in_planet(Geometric p) {
    double radius_point_p = (this->center - p).norm();
    return eqD(radius_point_p, this->radius);
}