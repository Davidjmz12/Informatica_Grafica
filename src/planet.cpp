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


bool collide(Planet s1, float az1, float inc1, Planet s2, float az2, float inc2)
{
    Base b1 = s1.base_point(inc1,az1); 
    Base b2 = s2.base_point(inc2,az2);
    SpatialElement* coord_b1 = b1.coord_from_canonical(new Point(b2._center));
    SpatialElement* coord_b2 = b2.coord_from_canonical(new Point(b1._center));
    
    return (*coord_b1)[2] < -THRESHOLD_FLOAT || (*coord_b2)[2] < -THRESHOLD_FLOAT;
}


Planet::Planet(Point center, Vector axis, Point ref_point)
    : _center(center), _ref_point(ref_point), _axis(axis), _radius(axis.norm())
{
    // Check if the ref_point is in the planet
    if (!this->point_in_planet(ref_point))
        throw std::invalid_argument("Error: The ref_point is not in the planet.");
}

Base Planet::base_point(float inclination, float azimut)
{
    //Compute the point
    LinearMap r1 = LinearMap::rotation(this->_axis,azimut);
    SpatialElement* s = new Vector(this->_ref_point-this->_center);
    SpatialElement* v1 = r1*s;
    Vector v1_vec = Vector(v1);
    Vector axis_second_rotation =  this->_axis.cross(&v1_vec);

    Vector aux = Vector(s).normalize();
    float angle_ref_axis = acos(this->_axis.normalize().dot(&aux));

    LinearMap r2 = LinearMap::rotation(axis_second_rotation,inclination - angle_ref_axis);

    Point point = Point(r2*v1) + Vector(this->_center);

    //Compute the axis
    Vector normal = (point-this->_center).normalize();
    Vector tangent_long = this->_axis.cross(&normal).normalize();
    Vector tangent_lat = normal.cross(&tangent_long);

    return Base(point, tangent_long, tangent_lat, normal);
}

bool Planet::point_in_planet(Point p) {
    float radius_point_p = (this->_center - p).norm();
    return eqFloat(radius_point_p, this->_radius);
}