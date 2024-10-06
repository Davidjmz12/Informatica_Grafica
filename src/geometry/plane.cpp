
#include "geometry/plane.hpp"


Plane::Plane(Point point, Vector normal)
    : _normal(normal.normalize()), _point(point)
{}

Plane::Plane(Point p1, Point p2, Point p3) 
{
    this->_normal = (p1-p2).cross(&(p3-p1)).normalize();
    this->_point = p1;
}


bool Plane::intersect_with_ray(const Ray& ray, Intersection& intersection) const
{
    double v_dot_n = ray.get_direction().dot(&this->_normal);

    if(eqD(v_dot_n, 0))
        return false;

    
    double distance = (this->_point - ray.get_point()).dot(&this->_normal) / v_dot_n;

    Point point = ray.evaluate(distance);

    Vector normal = (point-ray.get_point()).dot(&this->_normal)>0 ? this->_normal*(-1):this->_normal;

    intersection = Intersection(fabs(distance), normal, point);

    return true;
    
}

Vector Plane::get_normal() const
{
    return this->_normal;
}

Point Plane::get_point() const
{
    return this->_point;
}