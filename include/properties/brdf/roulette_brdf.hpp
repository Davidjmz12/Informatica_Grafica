#include "properties/brdf/brdf.hpp"

class RouletteBRDF : public BRDF {

private:
    std::vector<BRDF*> _brdfs;
    std::vector<double> _weights;
    int _sampled_ray_index;
public:

    RouletteBRDF(std::vector<BRDF*> brdfs, std::vector<double> weights);

    SpectralColor eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const override;

    bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering);

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const RouletteBRDF& b);
};