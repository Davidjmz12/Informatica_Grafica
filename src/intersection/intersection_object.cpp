#include "intersection/intersection_object.hpp"

IntersectionObject::IntersectionObject(double distance, Vector normal, Point point, Property properties, Vector origin)
    : Intersection(distance, origin, point), _normal(normal), _properties(properties)
{}

IntersectionObject::IntersectionObject()
{}

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

SpectralColor IntersectionObject::evalRenderEquation(SpectralColor power_light, Point point_light) const
{
    Vector c1_x = point_light-this->_point;
    SpectralColor Lwi = power_light/pow(c1_x.norm()+1,2);
    SpectralColor brdf = this->_properties.get_BRDF()->eval(this->_point,c1_x.normalize(), this->_origin);
    double cosine = fabs(this->_normal.dot(c1_x.normalize()));

    SpectralColor results = Lwi*brdf*cosine;

    return Lwi*brdf*cosine;
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
