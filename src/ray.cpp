#include "ray.hpp"

Ray::Ray(Point point, Vector direction)
    : _point(point), _direction(direction.normalize())
{}

Point Ray::evaluate(double t) const
{
    return _point+_direction*t;
} 

Point Ray::get_point() const
{
    return this->_point;
}

Vector Ray::get_direction() const
{
    return this->_direction;
}
