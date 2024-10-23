#include "properties/property.hpp"

Property::Property(Color color, BRDF* brdf):
    _color(color), _brdf(brdf)
{}

Property::Property()
    : _color(Color()), _brdf(new DiffuseBRDF())
{}

Color Property::get_color() const
{
    return this->_color;
}

BRDF* Property::get_BRDF() const
{
    return this->_brdf;
}
