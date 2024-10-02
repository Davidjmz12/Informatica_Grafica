/**
 * @file sphere.cpp
 * @brief Implementation of the sphere header.
 * @authors DavidJimenez DavidTizne
 * @date 18/09/2024
 * @see sphere.hpp for more information.
 * This file contains the implementation of sphere in R^3.
*/

#include <math.h>

#include "sphere.hpp"


bool collide(Sphere s1, float az1, float inc1, Sphere s2, float az2, float inc2)
{
    Base b1 = s1.base_point(inc1,az1); 
    Base b2 = s2.base_point(inc2,az2);
    Geometric coord_b1 = b1.coord_from_canonical(b2.center);
    Geometric coord_b2 = b2.coord_from_canonical(b1.center);
    
    return coord_b1[2] < -THRESHOLD_FLOAT || coord_b2[2] < -THRESHOLD_FLOAT;
}


Sphere::Sphere(Geometric center, Geometric axis, Geometric ref_point)
    : center(center), ref_point(ref_point), axis(axis), radius(axis.norm())
{
    // Check if the parameters are correct
    if (center.is_vector() || axis.is_point() || ref_point.is_vector())
        throw std::invalid_argument("Center and ref_point must be points. Axis must be a vector.");

    // Check if the ref_point is in the sphere
    if (!this->point_in_sphere(ref_point))
        throw std::invalid_argument("Error: The ref_point is not in the sphere.");
}

Base Sphere::base_point(float inclination, float azimut)
{
    //Compute the point
    LinearMap r1 = LinearMap::rotation(this->axis,azimut);
    Geometric v1 = r1*(this->ref_point-this->center);
    Geometric axis_second_rotation =  this->axis.cross(v1);

    float angle_ref_axis = acos(this->axis.normalize().dot((this->ref_point-this->center).normalize()));

    LinearMap r2 = LinearMap::rotation(axis_second_rotation,inclination - angle_ref_axis);

    Geometric point = r2*v1 + this->center;

    //Compute the axis
    Geometric normal = (point-this->center).normalize();
    Geometric tangent_long = this->axis.cross(normal).normalize();
    Geometric tangent_lat = normal.cross(tangent_long);

    return Base(point, tangent_long, tangent_lat, normal);
}

bool Sphere::point_in_sphere(Geometric p) {
    float radius_point_p = (this->center - p).norm();
    return eqFloat(radius_point_p, this->radius);
}