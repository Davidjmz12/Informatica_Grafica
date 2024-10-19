
#include "geometry/plane.hpp"


Plane::Plane(Point point, Vector normal, Property properties)
    : Geometry(properties), _normal(normal.normalize()), _distance(-Vector(point).dot(_normal))
{}

Plane::Plane(Vector normal, double distance, Property properties)
    : Geometry(properties), _normal(normal.normalize()), _distance(distance)
{}

Plane::Plane(Point p1, Point p2, Point p3, Property properties) 
    : Geometry(properties)
{
    this->_normal = (p1-p2).cross((p3-p1)).normalize();
    this->_distance = -Vector(p1).dot(this->_normal);
}


bool Plane::intersect_with_ray(const Ray& ray, Intersection& intersection) const
{
    double v_dot_n = ray.get_direction().dot(this->_normal);

    if(eqD(v_dot_n, 0))
        return false;
    
    double distance = (-this->_distance-Vector(ray.get_point()).dot(this->_normal))/(ray.get_direction().dot(this->_normal));

    if(ltD(distance,0))
        return false;

    Point point = ray.evaluate(distance);

    Vector normal = (ray.get_direction()).dot(this->_normal)>0 ? this->_normal*(-1):this->_normal;

    
    intersection = Intersection(distance, normal, point,this->_properties);

    return true;
    
}

Vector Plane::get_normal() const
{
    return this->_normal;
}

double Plane::get_distance() const
{
    return this->_distance;
}

std::ostream& operator<<(std::ostream& os, const Plane& p)
{
    os << p.to_string();
    return os;
}

std::string Plane::to_string() const
{
    return "Plane with normal: " + this->_normal.to_string() + " and distance: " + std::to_string(this->_distance);
}