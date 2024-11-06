#include "properties/brdf/specular_brdf.hpp"

SpecularBRDF::SpecularBRDF(const SpectralColor k)
    : BRDF(k)
{}

SpecularBRDF::SpecularBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor SpecularBRDF::eval(Vector w_i, IntersectionObject& intersection) const const
{
    return this->_k / intersection.get_normal().dot(intersection.get_dir_int()*(-1));
}

bool SpecularBRDF::sample_ray(const IntersectionObject& intersection, Ray& sampled_ray) const
{
    Vector w_i = intersection.get_dir_int()*(-1);
    Vector projection = w_i - intersection.get_normal()*w_i.dot(intersection.get_normal());

    Vector final_dir = w_i - projection * 2;
    
    sampled_ray = Ray(intersection.get_int_point(), final_dir, intersection.get_refraction_coefficient());
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

