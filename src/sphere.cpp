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

Sphere::Sphere(Geometric center, Geometric axis, Geometric ref_point)
    : center(center), ref_point(ref_point), axis(axis), radius(axis.norm() / 2)
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
    Linear_Map r1 = Linear_Map::rotation(this->axis,azimut);
    Geometric v1 = r1*this->ref_point-this->center;
    Geometric axis_second_rotation =  this->axis.cross(v1);

    float angle_ref_axis = acos(this->axis.normalize().dot((this->ref_point-this->center).normalize()));

    Linear_Map r2 = Linear_Map::rotation(axis_second_rotation,inclination - angle_ref_axis);

    Geometric point = r2*r1*this->ref_point;

    //Compute the axis
    Geometric normal = (point-this->center).normalize();
    Geometric tangent_long = this->axis.normalize().cross(normal);
    Geometric tangent_lat = tangent_long.cross(normal);

    return Base(point, tangent_long, tangent_lat, normal);
}

bool Sphere::point_in_sphere(Geometric p) {
    float radius_point_p = (this->center - p).norm();
    return radius_point_p == this->radius;
}