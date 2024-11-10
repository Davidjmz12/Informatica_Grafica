#include "properties/property.hpp"

Property::Property(BRDF* brdf):
    _brdf(brdf)
{}

Property::Property():
    _brdf(new DiffuseBRDF())
{}

SpectralColor Property::get_color() const
{
    return this->_brdf->get_color();
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
    return this->_brdf->to_string();
}