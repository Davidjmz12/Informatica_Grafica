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
    return g->intersect_with_ray(*this, intersection);
}

Geometric Ray::evaluate_point(float t) const
{
    return this->_point + this->_direction * t;
}
