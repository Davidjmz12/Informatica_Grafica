#include "intersection.hpp"

Intersection::Intersection(double distance, Geometric normal, Geometric point):
    _distance(distance),_normal(normal),_point(point){}

Intersection::Intersection():
    _distance(std::numeric_limits<double>::max()),_normal(Geometric::vector0()),_point(Geometric::point0()){}

Geometric Intersection::point() const
{
    return this->_point;
}

double Intersection::distance() const
{
    return this->_distance;
}

Geometric Intersection::normal() const
{
    return this->_normal;
}

Intersection Intersection::min(std::vector<Intersection> intersections)
{
    if(intersections.size() == 0)
        throw std::invalid_argument("The vector of intersections must have at least one element");
    Intersection min_intersection;
    for(auto intersection : intersections)
    {
        if(intersection.distance() < min_intersection.distance())
            min_intersection = intersection;
    }
    return min_intersection;
}