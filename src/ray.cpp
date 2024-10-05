#include "ray.hpp"

Ray::Ray(Geometric point, Geometric direction)
    : _point(point), _direction(direction.normalize())
{}

Geometric Ray::evaluate(double t) const
{
    return _point+_direction*t;
} 

Geometric Ray::point() const
{
    return this->_point;
}

Geometric Ray::direction() const
{
    return this->_direction;
}
