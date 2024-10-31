#include "intersection/intersection_light.hpp"

IntersectionLight::IntersectionLight()
    : Intersection(), _power(SpectralColor()), _origin(Vector())
{}

IntersectionLight::IntersectionLight(double distance, SpectralColor power, Vector origin)
    : Intersection(distance), _power(power), _origin(origin)
{}

SpectralColor IntersectionLight::get_power() const
{
    return _power;
}