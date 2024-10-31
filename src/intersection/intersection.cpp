#include "intersection/intersection.hpp"

Intersection::Intersection(double distance)
    : _distance(distance)
{}

Intersection::Intersection()
    : _distance(std::numeric_limits<double>::infinity())
{}

double Intersection::get_distance() const
{
    return this->_distance;
}

std::shared_ptr<Intersection> Intersection::min(std::vector<std::shared_ptr<Intersection>> intersections)
{
    if(intersections.size() == 0)
        throw std::invalid_argument("The vector of intersections must have at least one element");
    std::shared_ptr<Intersection> min_intersection = NULL;
    for(auto intersection : intersections)
    {
        if (min_intersection == NULL && gtD(intersection->get_distance(),0))
            min_intersection = intersection;
        else if (*intersection < *min_intersection && gtD(intersection->get_distance(),0))
            min_intersection = intersection;
    }
    return min_intersection;
}

bool Intersection::operator<(const Intersection& i) const
{
    return ltD(this->_distance,i.get_distance());
}

bool Intersection::operator>(const Intersection& i) const
{
    return gtD(this->_distance, i.get_distance());
}