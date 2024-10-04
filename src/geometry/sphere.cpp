#include "geometry/sphere.hpp"

Sphere::Sphere(Geometric center, float radius)
    : Ellipsoid(radius, radius, radius, center)
{}
