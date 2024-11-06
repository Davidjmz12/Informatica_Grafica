#include "properties/brdf/specular_brdf.hpp"

SpecularBRDF::SpecularBRDF(const SpectralColor k)
    : BRDF(k)
{}

SpecularBRDF::SpecularBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor SpecularBRDF::eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    return this->_k / n.dot(w_0);
}

bool SpecularBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray) const
{
    Vector projection = w_0 - n*w_0.dot(n);

    Vector final_dir = w_0 - projection * 2;
    
    sampled_ray = Ray(x, final_dir, ref_coef_entry);
    return true;
}

std::ostream& operator<<(std::ostream& os, const BRDF& b)
{
    os << b.to_string();
    return os;
}


std::string SpecularBRDF::to_string() const
{
    return "SpecularBRDF: " + this->_k.to_string();
}

