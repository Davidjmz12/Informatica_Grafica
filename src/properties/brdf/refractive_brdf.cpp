#include "properties/brdf/refractive_brdf.hpp"

RefractiveBRDF::RefractiveBRDF(const SpectralColor& k, const double refraction_coefficient)
    : BRDF(k), _refraction_coefficient(refraction_coefficient)
{}

RefractiveBRDF::RefractiveBRDF()
    : BRDF(SpectralColor()), _refraction_coefficient(0)
{
}

SpectralColor RefractiveBRDF::eval(Vector w_i, const Vector w_0, Point x, const Vector n, double ref_co_entry) const
{
    return this->_k / n.dot(w_0);
}

bool RefractiveBRDF::sample_ray(const Vector w_0, const Point x, const Vector n, double ref_co_entry,  Ray& sampled_ray, bool is_entering)
{
    
    const double theta_entry = acos(n.dot(w_0));

    const double entry_ri = is_entering ? 1 : this->_refraction_coefficient;
    const double exit_ri = is_entering ? this->_refraction_coefficient : 1;

    const double l = sin(theta_entry)*entry_ri/exit_ri;

    if(l>1 | l<-1)
        return false;

    const double theta_exit = asin(l);
    if(std::isnan(theta_exit))
        std::cout << "theta_exit is nan" << std::endl;
    const Vector orthogonal = ((w_0-n*w_0.dot(n))*(-1)).normalize();

    const auto base = Base(x, orthogonal, orthogonal.cross(n*(-1)) , n*(-1));
    std::unique_ptr<SpatialElement> v = std::make_unique<Vector>(sin(theta_exit),0,cos(theta_exit));
    const auto final_dir = Vector(base.coord_into_canonical(v.get()));

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