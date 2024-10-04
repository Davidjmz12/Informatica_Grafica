#include "ray.hpp"

Ray::Ray(Geometric point, Geometric direction)
    : _point(point), _direction(direction.normalize())
{}

Geometric Ray::evaluate(float t) const
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

Geometric Ray::evaluate_point(float t) const
{
    return this->_point + this->_direction * t;
}
