#include "light/light.hpp"

PunctualLight::PunctualLight(Point center, SpectralColor power)
    : _center(center), _power(power)
{}

SpectralColor PunctualLight::light_contribution(std::vector<Geometry*> geometries, const IntersectionObject& intersection) const
{
    
    return intersection.evalRenderEquation(this->_power, this->_center);
}
