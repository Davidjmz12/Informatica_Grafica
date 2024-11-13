
#include "geometry/bounding_box.hpp"

BoundingBox BoundingBox::get_BB_by_corners(const std::vector<Point>& corners)
{
    double max_x,min_x,max_y,min_y,max_z,min_z;
    for(const auto & corner : corners)
    {
        max_x = std::max(corner[0],max_x);
        min_x = std::min(corner[0],min_x);
        max_y = std::max(corner[1],max_y);
        min_y = std::min(corner[1],min_y);
        max_z = std::max(corner[2],max_z);
        min_z = std::min(corner[2],min_z);
    }
    return BoundingBox({min_x, max_x, min_y, max_y, min_z, max_z});
}

BoundingBox BoundingBox::combine_all(const std::vector<BoundingBox>& geometries)
{
    double max_x,min_x,max_y,min_y,max_z,min_z;
    for(const auto & geometry : geometries)
    {
        min_x = std::min(geometry._bound_box[0],min_x);
        max_x = std::max(geometry._bound_box[1],max_x);
        min_y = std::min(geometry._bound_box[2],min_y);
        max_y = std::max(geometry._bound_box[3],max_y);
        min_z = std::min(geometry._bound_box[4],min_z);
        max_z = std::max(geometry._bound_box[5],max_z);
    }
    return BoundingBox({min_x, max_x, min_y, max_y, min_z, max_z});
}

double BoundingBox::center(const size_t axis) const
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
    const Point rayOrigin = ray.get_point();
    const Vector rayDir = ray.get_direction();

    // Start with the intersection test along the x-axis
    double t_min = (this->_bound_box[0] - rayOrigin[0]) / rayDir[0];
    double t_max = (this->_bound_box[1] - rayOrigin[0]) / rayDir[0];
    if (t_min > t_max) std::swap(t_min, t_max);

    double ty_min = (this->_bound_box[2] - rayOrigin[1]) / rayDir[1];
    double ty_max = (this->_bound_box[3] - rayOrigin[1]) / rayDir[1];
    if (ty_min > ty_max) std::swap(ty_min, ty_max);

    if ((t_min > ty_max) || (ty_min > t_max))
        return false;

    if (ty_min > t_min)
        t_min = ty_min;
    if (ty_max < t_max)
        t_max = ty_max;

    double tz_min = (this->_bound_box[4] - rayOrigin[2]) / rayDir[2];
    double tz_max = (this->_bound_box[5] - rayOrigin[2]) / rayDir[2];
    if (tz_min > tz_max) std::swap(tz_min, tz_max);

    if ((t_min > tz_max) || (tz_min > t_max))
        return false;

    if (tz_min > t_min)
        t_min = tz_min;
    if (tz_max < t_max)
        t_max = tz_max;

    return t_max >= 0;
}

std::string BoundingBox::to_string() const
{
    std::string s;
    s += "X: [" + std::to_string(_bound_box[0]) + ", " + std::to_string(_bound_box[1]) + "] ";
    s += "Y: [" + std::to_string(_bound_box[2]) + ", " + std::to_string(_bound_box[3]) + "] ";
    s += "Z: [" + std::to_string(_bound_box[4]) + ", " + std::to_string(_bound_box[5]) + "] ";
    return s;
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bb)
{
    os << bb.to_string();
    return os;
}