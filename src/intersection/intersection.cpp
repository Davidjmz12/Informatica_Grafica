#include "intersection/intersection.hpp"

Intersection::Intersection(double distance, Vector origin)
    : _distance(distance), _origin(origin)
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

bool Intersection::operator<(const Intersection& i) const
{
    return ltD(this->_distance,i.get_distance());
}

bool Intersection::operator>(const Intersection& i) const
{
    return gtD(this->_distance, i.get_distance());
}