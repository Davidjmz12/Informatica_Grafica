
#include "geometry/triangle.hpp"

Triangle::Triangle(Point v0, Point v1, Point v2, Property properties)
    : Geometry(properties), _v0(v0), _v1(v1), _v2(v2)
{
    if(_v0 == _v1 || _v0 == _v2 || _v1 == _v2)
        throw std::invalid_argument("The vertices of the triangle must be different");
    if(eqD((_v1-_v0).cross((_v2-_v0)).norm(),0))
        throw std::invalid_argument("All three vertices of the triangle cannot be linearly dependent");
}

BoundingBox Triangle::get_bounding_box() const
{
    return BoundingBox::get_BB_by_corners({_v0,_v1,_v2});
}


Vector Triangle::get_normal() const
{
    return (this->_v1-this->_v0).cross((this->_v2-this->_v0)).normalize();
}

Plane Triangle::plane() const
{
    return Plane(this->_v0, this->get_normal(), this->_properties);
}

bool Triangle::point_inside_triangle(Point p) const
{
    Vector v0v1 = _v1 - _v0;
    Vector v0v2 = _v2 - _v0;
    Vector v0p = p - _v0;

    double dot00 = v0v2.dot(v0v2);
    double dot01 = v0v2.dot(v0v1);
    double dot02 = v0v2.dot(v0p);
    double dot11 = v0v1.dot(v0v1);
    double dot12 = v0v1.dot(v0p);

    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}


bool Triangle::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    Plane triangle_plane = this->plane();
    if(!triangle_plane.intersect_with_ray(r, intersection))
        return false;
    
    if(this->point_inside_triangle(intersection.get_point()))
    {
        return true;
    } 
    
    return false;
}

Point Triangle::operator[](int i) const
{
    if(i == 0)
        return this->_v0;
    else if(i == 1)
        return this->_v1;
    else if(i == 2)
        return this->_v2;
    else
        throw std::invalid_argument("Index out of bounds");
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    os << t.to_string();
    return os;
}

std::string Triangle::to_string() const
{
    return "Triangle: " + this->_v0.to_string() + " " + this->_v1.to_string() + " " + this->_v2.to_string();
}