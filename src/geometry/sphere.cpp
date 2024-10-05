#include "geometry/sphere.hpp"

Sphere::Sphere(Point center, float radius)
    : Ellipsoid(radius, radius, radius, center)
{}
