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

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
    os << r.to_string();
    return os;
}

std::string Ray::to_string() const
{
    return "Ray with point: " + this->_point.to_string() + " and direction: " + this->_direction.to_string();
}
