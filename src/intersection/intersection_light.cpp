#include "intersection/intersection_light.hpp"

IntersectionLight::IntersectionLight()
    : Intersection(), _power(SpectralColor())
{}

IntersectionLight::IntersectionLight(double distance, SpectralColor power, Vector origin, Point point)
    : Intersection(distance, origin, point), _power(power)
{}

SpectralColor IntersectionLight::get_power() const
{
    return _power;
}