#include "geometry/disk.hpp"

Disk::Disk(Point center, Vector normal, double radius):
    _plane(Plane(center, normal)), _radius(radius){}



bool Disk::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    if(!_plane.intersect_with_ray(r, intersection))
        return false;
        
    if( gtD((intersection.get_point()-_plane.get_point()).norm(), _radius) )
        return false;
    return true;
}