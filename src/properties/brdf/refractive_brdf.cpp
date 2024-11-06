#include "properties/brdf/refractive_brdf.hpp"

RefractiveBRDF::RefractiveBRDF(SpectralColor k, double refraction_coefficient)
    : BRDF(k), _refraction_coefficient(refraction_coefficient)
{}

RefractiveBRDF::RefractiveBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor RefractiveBRDF::eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    return this->_k / n.dot(w_0);
}

bool RefractiveBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray) const
{
    double theta_entry = acos(n.dot(w_0));
    
    double theta_exit = asin(sin(theta_entry)*ref_coef_entry/this->_refraction_coefficient);
    
    Vector orth = ((w_0-n*w_0.dot(n))*(-1)).normalize();

    Base base = Base(x, orth, orth.cross(n*(-1)) , n*(-1));
    
    Vector final_dir = Vector(base.coord_from_canonical(new Vector(sin(theta_exit),0,cos(theta_exit))));

    sampled_ray = Ray(x, final_dir, this->_refraction_coefficient);
    return true;
}

std::ostream& operator<<(std::ostream& os, const RefractiveBRDF& d)
{
    os << d.to_string();
    return os;
}

std::string RefractiveBRDF::to_string() const
{
    return "RefractiveBRDF: " + this->_k.to_string();
}