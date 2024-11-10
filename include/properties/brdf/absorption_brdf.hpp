#include "properties/brdf/brdf.hpp"

class AbsorptionBRDF : public BRDF {
public:
    AbsorptionBRDF();

    SpectralColor eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const override;

    bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) override;

    std::string to_string() const override;
    
    friend std::ostream& operator<<(std::ostream& os, const AbsorptionBRDF& b);
};
