#include "properties/brdf/diffuse_brdf.hpp"

DiffuseBRDF::DiffuseBRDF(Color k)
    : _k(k)
{}
    
DiffuseBRDF::DiffuseBRDF()
    : _k(Color())
{}

Color DiffuseBRDF::eval(Point p, Vector v, Vector w0) const
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
