#include "geometry/sphere.hpp"

Sphere::Sphere(Point center, double radius, std::shared_ptr<BRDF> brdf)
    : Ellipsoid(radius, radius, radius, center, brdf)
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