#include "geometry/sphere.hpp"

Sphere::Sphere(Point center, double radius)
    : Ellipsoid(radius, radius, radius, center)
{}

std::ostream& operator<<(std::ostream& os, const Sphere& s)
{
    os << s.to_string();
    return os;
}

std::string Sphere::to_string() const
{
    return "Sphere: " + this->_center.to_string() + " " + std::to_string(this->_a);
}