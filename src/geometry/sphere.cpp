#include "geometry/sphere.hpp"

Sphere::Sphere(Point center, double radius)
    : Ellipsoid(radius, radius, radius, center)
{}

std::ostream& operator<<(std::ostream& os, const Sphere& s)
{
    os << "Sphere: " << s._center << " " << s._a;
    return os;
}

