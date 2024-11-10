
#include "geometry/bounding_box.hpp"

BoundingBox BoundingBox::get_BB_by_corners(const std::vector<Point>& corners)
{
    double max_x,min_x,max_y,min_y,max_z,min_z;
    for(size_t i=0; i<corners.size(); i++)
    {
        max_x = std::max(corners[i][0],max_x);
        min_x = std::min(corners[i][0],min_x);
        max_y = std::max(corners[i][1],max_y);
        min_y = std::min(corners[i][1],min_y);
        max_z = std::max(corners[i][2],max_z);
        min_z = std::min(corners[i][2],min_z);
    }
    return BoundingBox({min_x, max_x, min_y, max_y, min_z, max_z});
}

BoundingBox BoundingBox::combine_all(const std::vector<BoundingBox> geometries)
{
    double max_x,min_x,max_y,min_y,max_z,min_z;
    for(size_t i=0; i<geometries.size(); i++)
    {
        max_x = std::max(geometries[i]._bound_box[1],max_x);
        min_x = std::min(geometries[i]._bound_box[0],min_x);
        max_y = std::max(geometries[i]._bound_box[3],max_y);
        min_y = std::min(geometries[i]._bound_box[2],min_y);
        max_z = std::max(geometries[i]._bound_box[5],max_z);
        min_z = std::min(geometries[i]._bound_box[4],min_z);
    }
    return BoundingBox({min_x, max_x, min_y, max_y, min_z, max_z});
}

double BoundingBox::center(size_t axis) const
{
    return (_bound_box[2*axis] + _bound_box[2*axis+1])/2;
}

BoundingBox::BoundingBox() 
    : _bound_box({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                  -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                  -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})
{}

// Constructor that accepts a std::array<double, 6>
BoundingBox::BoundingBox(const std::array<double, 6>& bounds) 
    : _bound_box(bounds)
{}

// Function to check if a ray intersects the bounding box
bool BoundingBox::intersect_with_ray(const Ray& ray) const {
    Point rayOrigin = ray.get_point();
    Vector rayDir = ray.get_direction();

    // Start with the intersection test along the x-axis
    double tmin = (_bound_box[0] - rayOrigin[0]) / rayDir[0];
    double tmax = (_bound_box[1] - rayOrigin[0]) / rayDir[0];
    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (_bound_box[2] - rayOrigin[1]) / rayDir[1];
    double tymax = (_bound_box[3] - rayOrigin[1]) / rayDir[1];
    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (_bound_box[4] - rayOrigin[2]) / rayDir[2];
    double tzmax = (_bound_box[5] - rayOrigin[2]) / rayDir[2];
    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return tmax >= 0;
}