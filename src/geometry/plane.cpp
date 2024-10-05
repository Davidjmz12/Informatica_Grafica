
#include "geometry/plane.hpp"


Plane::Plane(Geometric point, Geometric normal)
    : Geometry(), _normal(normal.normalize()), _point(point)
{}

Plane::Plane(Geometric p1, Geometric p2, Geometric p3) 
{
    this->_normal = (p1-p2).cross((p3-p1)).normalize();
    this->_point = p1;
}

float Plane::implicit(Geometric x) const
{
    return this->_normal.dot(x-this->_point);
}

bool Plane::intersect_with_ray(const Ray& ray, Intersection& intersection) const
{
    float v_dot_n = ray.direction().dot(this->_normal);
    if(eqFloat(v_dot_n, 0))
        return false;

    
    float distance = (this->_point - ray.point()).dot(this->_normal) / v_dot_n;

    Geometric point = ray.evaluate(distance);

    Geometric normal = (point-ray.point()).dot(this->_normal)>0 ? this->_normal*(-1):this->_normal;

    intersection = Intersection(fabs(distance), normal, point);

    return true;
    
}

Geometric Plane::normal() const
{
    return this->_normal;
}

Geometric Plane::point() const
{
    return this->_point;
}