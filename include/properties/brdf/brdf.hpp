#pragma once

#include "color/spectral_color.hpp"
#include "intersection/intersection_object.hpp"
#include "scene/ray.hpp"


class BRDF {
protected:
    SpectralColor _k; // The color of the object

public:
    BRDF(SpectralColor k);

    virtual SpectralColor eval(Vector w_i, IntersectionObject& intersection) const = 0;

    virtual bool sample_ray(const IntersectionObject& intersection, Ray& sampled_ray) const = 0;

    virtual std::string to_string() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);
};
