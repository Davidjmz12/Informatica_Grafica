#include "intersection.hpp"


Intersection::Intersection(double distance, Vector normal, Point point):
    _distance(distance),_normal(normal),_point(point){}

Intersection::Intersection():
    _distance(std::numeric_limits<double>::max()),_normal(Vector()),_point(Point()){}

Point Intersection::get_point() const
{
    return this->_point;
}

double Intersection::get_distance() const
{
    return this->_distance;
}

Vector Intersection::get_normal() const
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
        if(intersection.get_distance() < min_intersection.get_distance())
            min_intersection = intersection;
    }
    return min_intersection;
}

bool Intersection::operator==(const Intersection i) const
{
    return  eqD(this->_distance,i._distance) &&
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
