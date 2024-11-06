#pragma once

#include "brdf.hpp"

class DiffuseBRDF : public BRDF
{
public:
    DiffuseBRDF(SpectralColor k);

    DiffuseBRDF();
    
    SpectralColor eval(Vector w_i, IntersectionObject& intersection) const override;

    bool sample_ray(const IntersectionObject& intersection, Ray& sampled_ray) const override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d);
};
