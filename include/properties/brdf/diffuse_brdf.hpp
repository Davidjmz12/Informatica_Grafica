#pragma once

#include "brdf.hpp"

class DiffuseBRDF : public BRDF
{
public:
    DiffuseBRDF(SpectralColor k);

    DiffuseBRDF();
    
    SpectralColor eval(SpectralColor light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const override;

    bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d);

    bool is_delta() const override;
};
