#include "intersection/intersection.hpp"

Intersection::Intersection(double distance, Vector origin, Point point)
    : _distance(distance), _origin(origin), _point(point)
{}

Intersection::Intersection()
    : _distance(std::numeric_limits<double>::infinity())
{}

double Intersection::get_distance() const
{
    return this->_distance;
}

Vector Intersection::get_origin() const
{
    return this->_origin;
}

Point Intersection::get_point() const
{
    return this->_point;
}

bool Intersection::operator<(const Intersection& i) const
{
    return ltD(this->_distance,i.get_distance());
}

bool Intersection::operator>(const Intersection& i) const
{
    return gtD(this->_distance, i.get_distance());
}