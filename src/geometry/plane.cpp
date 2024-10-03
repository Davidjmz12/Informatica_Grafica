
#include "geometry/plane.hpp"


Plane::Plane(Geometric normal, Geometric point)
    : Geometry(), _normal(normal.normalize()), _point(point), _d(-point.dot(normal))
{}

Plane::Plane(Geometric p1, Geometric p2, Geometric p3) 
{
    this->_normal = (p1-p2).cross((p3-p1)).normalize();
    this->_point = p1;
    this->_d = -p1.dot(_normal);
}

float Plane::implicit(Geometric x) const
{
    return this->_normal.dot(x) + this->_d;
}

bool Plane::intersect_with_ray(const Ray& ray, Intersection& intersection) const
{
    if(eqFloat(ray.direction().dot(this->_normal), 0) && !eqFloat(this->implicit(ray.point()), 0) )
        return false;

    
    float distance = - (this->_d+ray.point().dot(this->_normal))/ray.direction().dot(this->_normal);

    Geometric point = ray.point() + ray.direction()*distance;

    Geometric normal = this->_normal;

    intersection = Intersection(distance,normal,point);

    return true;
    
}