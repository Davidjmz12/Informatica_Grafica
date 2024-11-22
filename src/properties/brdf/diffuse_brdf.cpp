#include "properties/brdf/diffuse_brdf.hpp"

DiffuseBRDF::DiffuseBRDF(Color k)
    : BRDF(k)
{}
    
DiffuseBRDF::DiffuseBRDF()
    : BRDF(Color())
{}

Color DiffuseBRDF::eval(Color light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    return light * this->_k / M_PI;
}

bool DiffuseBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering)
{
    double phi = randomD(0,2*M_PI);
    double theta = randomD(0,1);
    theta = asin(theta);

    Base b = Base::complete_base_k(x, n);

    std::unique_ptr<SpatialElement> base_v = std::make_unique<Vector>(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
    Vector v = Vector(b.coord_into_canonical(base_v.get()));
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

bool DiffuseBRDF::is_delta() const
{
    return false;
}