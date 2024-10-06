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
    SpatialElement* coord_b1 = b1.coord_from_canonical(new Point(b2._center));
    SpatialElement* coord_b2 = b2.coord_from_canonical(new Point(b1._center));
    
    return leF((*coord_b1)[2],0) || leF((*coord_b2)[2],0);
}

LinearMap Planet::compute_azimut_rotation(const LinearMap* r) const
{
    Vector e1 = Vector(1,0,0);
    SpatialElement* ref_point_centered_aux = new Vector(this->_ref_point - Vector(this->_center));
    Point ref_point_centered = Point((*r)*ref_point_centered_aux);

    // Rotation to fix azimut
    Vector ref_proyected = Vector(  ref_point_centered[0],
                                    ref_point_centered[1],
                                    0).normalize();
    LinearMap res = LinearMap::identity();
    if (!(ref_proyected.normalize() == e1))
    {
        Vector axis_ref = ref_proyected.cross(&e1);
        double angle_first_rotation;
        if (axis_ref == Vector())
        {
            axis_ref = Vector(0,0,1);
            angle_first_rotation = M_PI;
        }
        else
            angle_first_rotation = acos(ref_proyected.dot(&e1));
        res = LinearMap::rotation(axis_ref,-angle_first_rotation);
    }

    return res;
}

LinearMap Planet::compute_axis_rotation() const
{
    Vector e3 = Vector(0,0,1);

    // Roatation to fix axe
    LinearMap r = LinearMap::identity();
    if (!(this->_axis.normalize() == e3))
    {
        Vector axis_second_rotation = this->_axis.cross(&e3);
        double angle_second_rotation = acos(e3.dot(&this->_axis) / this->_radius);

        r = LinearMap::rotation(axis_second_rotation,
                                angle_second_rotation);
    }

    return r;
}

Planet::Planet(Point center, Vector axis, Point ref_point)
    : _center(center), _ref_point(ref_point), _axis(axis), _radius(axis.norm())
{
    // Check if the ref_point is in the planet
    if (!this->point_in_planet(ref_point))
        throw std::invalid_argument("Error: The ref_point is not in the planet.");

    LinearMap r2 = this->compute_axis_rotation();
    LinearMap r1 = this->compute_azimut_rotation(&r2);

    // Final traslation
    LinearMap t = LinearMap::translation(Vector(this->_center));

    // Composition of movements
    this->_compute_point = t*r1*r2;
}

Point Planet::parametric_point(double inclination, double azimut) const
{
    Vector p = Vector(  sin(inclination)*cos(azimut),
                        sin(inclination)*sin(azimut),
                        cos(inclination));
    return Point(p * this->_radius);
}

Base Planet::base_point(double inclination, double azimut)
{
    SpatialElement* initial_point = new Point(parametric_point(inclination, azimut));
    Point point = Point(this->_compute_point * initial_point);

    //Compute the axis
    Vector normal = (point-this->_center).normalize();
    Vector tangent_long = this->_axis.cross(&normal).normalize();
    Vector tangent_lat = normal.cross(&tangent_long);

    return Base(point, tangent_long, tangent_lat, normal);
}

bool Planet::point_in_planet(Point p) {
    double radius_point_p = (this->_center - p).norm();
    return eqD(radius_point_p, this->_radius);
}