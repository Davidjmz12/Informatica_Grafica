#include "geometry/disk.hpp"

Disk::Disk(Geometric center, Geometric normal, float radius):
    _plane(Plane(center, normal)), _radius(radius){}

float Disk::implicit(Geometric x) const
{
    return _plane.implicit(x);
}

bool Disk::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    if(!_plane.intersect_with_ray(r, intersection))
        return false;
    if( gtFloat((intersection.point()-_plane.point()).norm(), _radius) )
        return false;
    return true;
}