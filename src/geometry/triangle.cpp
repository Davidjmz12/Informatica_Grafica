
#include "geometry/triangle.hpp"

Triangle::Triangle(Geometric v0, Geometric v1, Geometric v2)
    : _v0(v0), _v1(v1), _v2(v2)
{
    if(_v0 == _v1 || _v0 == _v2 || _v1 == _v2)
        throw std::invalid_argument("The vertices of the triangle must be different");
}


Geometric Triangle::normal() const
{
    return (this->_v1-this->_v0).cross((this->_v2-this->_v0)).normalize();
}

Plane Triangle::plane() const
{
    return Plane(this->_v0, this->normal());
}

double Triangle::implicit(Geometric x) const
{
    return plane().implicit(x);
}

bool Triangle::point_inside_triangle(Geometric p) const
{
    Geometric v0v1 = _v1 - _v0;
    Geometric v0v2 = _v2 - _v0;
    Geometric v0p = p - _v0;

    double dot00 = v0v2.dot(v0v2);
    double dot01 = v0v2.dot(v0v1);
    double dot02 = v0v2.dot(v0p);
    double dot11 = v0v1.dot(v0v1);
    double dot12 = v0v1.dot(v0p);

    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}


bool Triangle::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    Intersection plane_intersection;
    Plane triangle_plane = this->plane();
    if(!triangle_plane.intersect_with_ray(r, plane_intersection))
        return false;
    
    if(this->point_inside_triangle(plane_intersection.point()))
    {
        intersection = plane_intersection;
        return true;
    } 
    
    return false;
}