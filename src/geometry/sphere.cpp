#include "geometry/sphere.hpp"

Sphere::Sphere(Point center, double radius)
    : Ellipsoid(radius, radius, radius, center)
{}
