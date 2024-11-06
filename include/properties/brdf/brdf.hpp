#pragma once

#include "spatial_element/point.hpp"
#include "spatial_element/vector.hpp"
#include "color/spectral_color.hpp"
#include "intersection/intersection_object.hpp"

class BRDF {
protected:
    SpectralColor _k; // The color of the object

public:
    BRDF(SpectralColor k)
        : _k(k) {}

    virtual SpectralColor eval(Vector v, IntersectionObject& i) const = 0;

    virtual bool sample_ray(const IntersectionObject& inter, Ray& sampled_ray) const = 0;

    virtual std::string to_string() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);
};
