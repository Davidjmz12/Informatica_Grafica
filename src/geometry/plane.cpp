
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

BoundingBox Plane::get_bounding_box() const
{
    return BoundingBox();
}


bool Plane::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    double v_dot_n = r.get_direction().dot(this->_normal);

    if(eqD(v_dot_n, 0))
        return false;
    
    double distance = (-this->_distance-Vector(r.get_point()).dot(this->_normal))/(r.get_direction().dot(this->_normal));

    if(leD(distance,0))
        return false;

    Point point = r.evaluate(distance);

    Vector normal = (r.get_direction()).dot(this->_normal)>0 ? this->_normal*(-1):this->_normal;

    
    intersection = IntersectionObject(distance, normal, point,this->_properties, r);

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