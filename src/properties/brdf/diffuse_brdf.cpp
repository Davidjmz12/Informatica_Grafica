#include "properties/brdf/diffuse_brdf.hpp"

DiffuseBRDF::DiffuseBRDF(SpectralColor k)
    : BRDF(k)
{}
    
DiffuseBRDF::DiffuseBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor DiffuseBRDF::eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    return this->_k / M_PI;
}

bool DiffuseBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray) const
{
    double phi = randomD(0,2*M_PI);
    double theta = randomD(0,1);
    theta = acos(sqrt(1-theta));

    Base b = Base::complete_base_k(x, n);

    Vector v = Vector(b.coord_into_canonical(new Vector(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta))));
    sampled_ray = Ray(x, v, ref_coef_entry);
    return true;
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
