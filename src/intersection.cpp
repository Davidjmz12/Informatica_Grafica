#include "intersection.hpp"

Intersection::Intersection():
    _distance(std::numeric_limits<float>::max()),_normal(Vector()),_point(Point()){}

Intersection::Intersection(float distance, Vector normal, Point point):
    _distance(distance),_normal(normal),_point(point){}

Point Intersection::get_point() const
{
    return this->_point;
}

float Intersection::distance() const
{
    return this->_distance;
}

Vector Intersection::get_normal() const
{
    return this->_normal;
}

Intersection Intersection::min(std::vector<Intersection> intersections) const
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

bool Intersection::operator==(const Intersection i) const
{
    return  eqFloat(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_point == i._point;
}

std::ostream& operator<<(std::ostream& os, const Intersection& i)
{
    std::string str = "hola";
    os  << std::string("Intersection:\n\tPoint:\t") << i._point
        << std::string("\tNormal:\t") << i._normal
        << std::string("\tDistance:\t") << std::to_string(i._distance);
    return os;
}
