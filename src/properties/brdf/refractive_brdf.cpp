#include "properties/brdf/refractive_brdf.hpp"

RefractiveBRDF::RefractiveBRDF(SpectralColor k, double refraction_coefficient)
    : BRDF(k), _refraction_coefficient(refraction_coefficient)
{}

RefractiveBRDF::RefractiveBRDF()
    : BRDF(SpectralColor())
{}

SpectralColor RefractiveBRDF::eval(Vector w_i, IntersectionObject& intersection) const
{
    return this->_k / intersection.get_normal().dot(intersection.get_dir_int()*(-1));
}

bool RefractiveBRDF::sample_ray(const IntersectionObject& intersection, Ray& sampled_ray) const
{
    double theta_entry = acos(intersection.get_normal().dot(intersection.get_dir_int()*(-1)));
    
    double theta_exit = asin(sin(theta_entry)/intersection.get_refraction_coefficient()*this->_refraction_coefficient);
    
    Vector orth = (intersection.get_dir_int()-intersection.get_normal()*intersection.get_dir_int().dot(intersection.get_normal())).normalize();

    Base base = Base(intersection.get_int_point(), orth, orth.cross(intersection.get_normal()*(-1)) , intersection.get_normal()*(-1));
    
    Vector final_dir = Vector(base.coord_from_canonical(new Vector(sin(theta_exit),0,cos(theta_exit))));

    sampled_ray = Ray(intersection.get_int_point(), final_dir);
    return true;
}