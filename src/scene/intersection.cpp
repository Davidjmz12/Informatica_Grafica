#include "scene/intersection.hpp"


Intersection::Intersection(double distance, Vector normal, Point point, Property properties, Vector origin):
    _distance(distance), _normal(normal), _point(point), _properties(properties), _origin(origin)
{}

Intersection::Intersection():
    _distance(std::numeric_limits<double>::max()),_normal(Vector()),
    _point(Point()),_properties(Property())
{}

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

Property Intersection::get_properties() const
{
    return this->_properties;
}

Vector Intersection::get_origin() const
{
    return this->_origin;
}

Intersection Intersection::min(std::vector<Intersection> intersections)
{
    if(intersections.size() == 0)
        throw std::invalid_argument("The vector of intersections must have at least one element");
    Intersection min_intersection;
    for(auto intersection : intersections)
    {
        if(intersection < min_intersection)
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

bool Intersection::operator<(const Intersection i) const
{
    return ltD(this->_distance, i._distance);
}

bool Intersection::operator>(const Intersection i) const
{
    return gtD(this->_distance, i._distance);
}

std::ostream& operator<<(std::ostream& os, const Intersection& i)
{
    os  << std::string("Intersection:\n\tPoint:\t") << i._point
        << std::string("\tNormal:\t") << i._normal
        << std::string("\tDistance:\t") << std::to_string(i._distance)
        << std::string("\tProperties:\t") << i._properties
        << std::string("\tOrigin:\t") << i._origin;
    return os;
}
