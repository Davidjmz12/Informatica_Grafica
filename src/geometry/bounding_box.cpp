
#include "geometry/bounding_box.hpp"

// Constructor that accepts a std::array<double, 6>
BoundingBox::BoundingBox(const std::array<double, 6>& bounds) 
    : _bound_box(bounds)
{}

// Function to check if a ray intersects the bounding box
bool BoundingBox::intersects_with_ray(const Ray& ray) const {
    Point rayOrigin = ray.get_point();
    Vector rayDir = ray.get_direction();

    // Start with the intersection test along the x-axis
    double tmin = (_bound_box[0] - rayOrigin[0]) / rayDir[0];
    double tmax = (_bound_box[1] - rayOrigin[0]) / rayDir[0];
    if (tmin > tmax) std::swap(tmin, tmax);

    // Then check along the y-axis
    double tymin = (_bound_box[2] - rayOrigin[1]) / rayDir[1];
    double tymax = (_bound_box[3] - rayOrigin[1]) / rayDir[1];
    if (tymin > tymax) std::swap(tymin, tymax);

    // Early exit if no intersection is possible
    if ((tmin > tymax) || (tymin > tmax))
        return false;

    // Update tmin and tmax to ensure correct intersection on all axes
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    // Now check along the z-axis
    double tzmin = (_bound_box[4] - rayOrigin[2]) / rayDir[2];
    double tzmax = (_bound_box[5] - rayOrigin[2]) / rayDir[2];
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    // Final intersection check
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    // Intersection happens if the ray hits the box in front of the origin
    return tmax >= 0;
}