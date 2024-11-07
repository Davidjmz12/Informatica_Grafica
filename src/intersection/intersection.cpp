#include "intersection/intersection.hpp"

Intersection::Intersection(double distance, Point intersection_point, Ray ray)
    : _distance(distance), _intersection_point(intersection_point), _ray(ray)
{}

Intersection::Intersection()
    : _distance(std::numeric_limits<double>::infinity())
{}

double Intersection::get_distance() const
{
    return this->_distance;
}

Point Intersection::get_int_point() const
{
    return this->_intersection_point;
}

Vector Intersection::get_dir_int() const
{
    return this->_ray.get_direction();
}

Point Intersection::get_origin() const
{
    return this->_ray.get_point();
}

double Intersection::get_refraction_coefficient() const
{
    return this->_ray.get_refraction_coefficient();
}

Ray Intersection::get_ray() const
{
    return this->_ray;
}

bool Intersection::operator<(const Intersection& i) const
{
    return ltD(this->_distance,i.get_distance());
}

bool Intersection::operator>(const Intersection& i) const
{
    return gtD(this->_distance, i.get_distance());
}

std::ostream& operator<<(std::ostream& os, const Intersection& i)
{
    os << i.to_string();
    return os;
}

std::string Intersection::to_string() const
{
    return "Intersection: " + this->_intersection_point.to_string() + "\n" + std::to_string(this->_distance);
}