#include "intersection.hpp"

Intersection::Intersection(float distance, Geometric normal, Geometric point):
    _distance(distance),_normal(normal),_point(point){}

Intersection::Intersection():
    _distance(std::numeric_limits<float>::max()),_normal(Geometric::vector0()),_point(Geometric::point0()){}

Geometric Intersection::point() const
{
    return this->_point;
}

float Intersection::distance() const
{
    return this->_distance;
}

Geometric Intersection::normal() const
{
    return this->_normal;
}