#include "intersection/intersection_light.hpp"

IntersectionLight::IntersectionLight()
    : Intersection(), _power(Color())
{}

IntersectionLight::IntersectionLight(double distance, Color power, Point intersection_point, Ray ray)
    : Intersection(distance, intersection_point, ray), _power(power)
{}

Color IntersectionLight::get_power() const
{
    return _power;
}

std::ostream& operator<<(std::ostream& os, const IntersectionLight& i)
{
    os << i.to_string();
    return os;
}

std::string IntersectionLight::to_string() const
{
    return "IntersectionLight: " + this->_intersection_point.to_string() + "\n" + std::to_string(this->_distance) + "\n" + this->_power.to_string();
}