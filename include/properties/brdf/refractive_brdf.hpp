#pragma once

#include "brdf.hpp"
#include "spatial_element/base.hpp"

class RefractiveBRDF : public BRDF
{
private:
    double _refraction_coefficient;
public:
    RefractiveBRDF(SpectralColor k, double refraction_coefficient);

    RefractiveBRDF();
    
    SpectralColor eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const override;

    bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const RefractiveBRDF& d);
};