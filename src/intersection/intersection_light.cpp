#include "intersection/intersection_light.hpp"

IntersectionLight::IntersectionLight()
    : Intersection(), _power(SpectralColor())
{}

IntersectionLight::IntersectionLight(double distance, SpectralColor power, Point intersection_point, Ray ray)
    : Intersection(distance, intersection_point, ray), _power(power)
{}

SpectralColor IntersectionLight::get_power() const
{
    return _power;
}