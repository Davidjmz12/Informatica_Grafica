#include "geometry/disk.hpp"

Disk::Disk(Point center, Vector normal, double radius, Property properties)
    : Geometry(properties), _plane(Plane(center, normal, properties)), _center(center), _normal(normal), _radius(radius){}



BoundingBox Disk::get_bounding_box() const
{
    return BoundingBox(
        {
            this->_center[0]-this->_radius, this->_center[0]+this->_radius,
            this->_center[1]-this->_radius, this->_center[1]+this->_radius,
            this->_center[2]-this->_radius, this->_center[2]+this->_radius
        }
    );
}

bool Disk::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    if(!_plane.intersect_with_ray(r, intersection))
        return false;
        
    if(gtD((intersection.get_int_point()-this->_center).norm(), _radius))
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Disk& d)
{
    os << d.to_string();
    return os;
}

std::string Disk::to_string() const
{
    return "Disk in plane:\n" + this->_plane.to_string() + "\nRadius: " + std::to_string(this->_radius);
}