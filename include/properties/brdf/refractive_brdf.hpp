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
    
    SpectralColor eval(Vector w_i, IntersectionObject& intersection) const override;

    bool sample_ray(const IntersectionObject& intersection, Ray& sampled_ray) const override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d);
};