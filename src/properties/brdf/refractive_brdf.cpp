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

bool RefractiveBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry,  Ray& sampled_ray, bool is_entering) const
{
    
    double theta_entry = acos(n.dot(w_0));

    double entry_ri = is_entering ? 1 : this->_refraction_coefficient;
    double exit_ri = is_entering ? this->_refraction_coefficient : 1;

    double l = sin(theta_entry)*entry_ri/exit_ri;

    if(l>1 | l<-1)
        return false;

    double theta_exit = asin(l);
    if(std::isnan(theta_exit))
        std::cout << "theta_exit is nan" << std::endl;
    Vector orth = ((w_0-n*w_0.dot(n))*(-1)).normalize();

    Base base = Base(x, orth, orth.cross(n*(-1)) , n*(-1));
    
    Vector final_dir = Vector(base.coord_into_canonical(new Vector(sin(theta_exit),0,cos(theta_exit))));

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