#pragma once

#include "brdf.hpp"
#include "spatial_element/base.hpp"

class RefractiveBRDF final : public BRDF
{
private:
    double _refraction_coefficient;
public:
    RefractiveBRDF(const SpectralColor& k, double refraction_coefficient);

    RefractiveBRDF();
    
    [[nodiscard]] SpectralColor eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_co_entry) const override;

    bool sample_ray(Vector w_0, Point x, Vector n, double ref_co_entry, Ray& sampled_ray, bool is_entering) override;

    [[nodiscard]]  std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const RefractiveBRDF& d);

    bool is_delta() const override;
};