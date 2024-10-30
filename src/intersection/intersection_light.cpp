#include "intersection/intersection_light.hpp"

IntersectionLight::IntersectionLight(double distance, SpectralColor power, Vector origin)
    : Intersection(distance), _power(power), _origin(origin)
{}

