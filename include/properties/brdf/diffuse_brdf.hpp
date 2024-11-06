#pragma once

#include "brdf.hpp"

/**
 * @brief Class that represents the diffuse property of
 * an object
 */
class DiffuseBRDF : public BRDF
{
public:
    DiffuseBRDF(SpectralColor k);

    DiffuseBRDF();
    
    SpectralColor eval(Vector v, IntersectionObject& i) const override;

    bool sample_ray(const IntersectionObject& inter, Ray& sampled_ray) const override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d);
};
