#include "properties/property.hpp"

Property::Property(Color color, BRDF* brdf):
    _color(color), _brdf(brdf)
{}

Property::Property(Color color)
    : _color(color), _brdf(new DiffuseBRDF(color))
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

std::ostream& operator<<(std::ostream& os, const Property& p)
{
    os << p.to_string();
    return os;
}

std::string Property::to_string() const
{
    return "Color: " + this->_color.to_string() + "\n" + this->_brdf->to_string();
}