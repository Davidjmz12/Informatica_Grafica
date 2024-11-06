#pragma once

#include "properties/brdf/brdf.hpp"

class SpecularBRDF : public BRDF
{
public:
    SpecularBRDF();
    SpecularBRDF(const SpectralColor k);

    SpectralColor eval(Vector v, IntersectionObject& i) const override;

    bool sample_ray(const IntersectionObject& inter, Ray& sampled_ray) const override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);
};
