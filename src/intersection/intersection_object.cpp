#include "intersection/intersection_object.hpp"

IntersectionObject::IntersectionObject(double distance, Vector normal, Point point, Property properties, Vector origin)
    : Intersection(distance, origin), _normal(normal), _point(point), _properties(properties)
{}

IntersectionObject::IntersectionObject()
    : Intersection(std::numeric_limits<double>::max(), Vector()),_normal(Vector()),
    _point(Point()),_properties(Property())
{}

Point IntersectionObject::get_point() const
{
    return this->_point;
}

Vector IntersectionObject::get_normal() const
{
    return this->_normal;
}

Property IntersectionObject::get_properties() const
{
    return this->_properties;
}

bool IntersectionObject::operator==(const IntersectionObject i) const
{
    return  eqD(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_point == i._point;
}

std::ostream& operator<<(std::ostream& os, const IntersectionObject& i)
{
    os  << std::string("Intersection:\n\tPoint:\t") << i._point
        << std::string("\tNormal:\t") << i._normal
        << std::string("\tDistance:\t") << std::to_string(i._distance)
        << std::string("\tProperties:\t") << i._properties
        << std::string("\tOrigin:\t") << i._origin;
    return os;
}
