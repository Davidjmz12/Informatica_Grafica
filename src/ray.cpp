#include "ray.hpp"

Ray::Ray(Geometric point, Geometric direction)
    : _point(point), _direction(direction.normalize())
{}

Geometric Ray::point() const
{
    return this->_point;
}

Geometric Ray::direction() const
{
    return this->_direction;
}

bool Ray::intersects_with_geometry(Geometry* g, Intersection& intersection)
{
    g->intersect_with_ray(*this, intersection);
}