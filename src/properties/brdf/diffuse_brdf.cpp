#include "properties/brdf/diffuse_brdf.hpp"

DiffuseBRDF::DiffuseBRDF(SpectralColor k)
    : BRDF(k)
{}
    
DiffuseBRDF::DiffuseBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor DiffuseBRDF::eval(Vector v, Intersection& i) const
{
    return this->_k / M_PI;
}


std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d)
{
    os << d.to_string();
    return os;
}

std::string DiffuseBRDF::to_string() const
{
    return "DiffuseBRDF: " + this->_k.to_string();
}
