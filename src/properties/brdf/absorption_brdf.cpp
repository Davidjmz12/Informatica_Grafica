#include "properties/brdf/absorption_brdf.hpp"

AbsorptionBRDF::AbsorptionBRDF() : BRDF(Color()) {}

Color AbsorptionBRDF::eval(Color light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    return Color();
}

bool AbsorptionBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering)
{
    return false;
}

std::string AbsorptionBRDF::to_string() const
{
    return "AbsorptionBRDF";
}

std::ostream& operator<<(std::ostream& os, const AbsorptionBRDF& b)
{
    os << b.to_string();
    return os;
}

bool AbsorptionBRDF::is_delta() const
{
    return false;
}