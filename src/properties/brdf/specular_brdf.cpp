#include "properties/brdf/specular_brdf.hpp"

SpecularBRDF::SpecularBRDF(const SpectralColor k)
    : BRDF(k)
{}

SpecularBRDF::SpecularBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor SpecularBRDF::eval(Vector v, IntersectionObject& i) const const
{
    return this->_k / i.get_normal().dot(i.get_dir_int());
}

bool SpecularBRDF::sample_ray(const IntersectionObject& inter, Ray& sampled_ray) const
{
    Vector projection = inter.get_dir_int() - inter.get_normal()*inter.get_dir_int().dot(inter.get_normal());

    Vector final_dir = inter.get_dir_int() - projection * 2;
    
    sampled_ray = Ray(inter.get_int_point(), final_dir);
    return true;
}

std::string to_string() const
{

}

friend std::ostream& operator<<(std::ostream& os, const BRDF& b)
{

}
