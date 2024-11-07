#pragma once

#include "color/spectral_color.hpp"
#include "scene/ray.hpp"
#include "spatial_element/base.hpp"


class BRDF {
protected:
    SpectralColor _k; // The color of the object

public:
    BRDF(SpectralColor k);

    virtual SpectralColor eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const = 0;

    virtual bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const = 0;

    virtual std::string to_string() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);
};
