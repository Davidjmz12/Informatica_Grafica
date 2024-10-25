#pragma once

#include "spatial_element/point.hpp"
#include "spatial_element/vector.hpp"
#include "color/spectral_color.hpp"

class BRDF {
public:
    virtual SpectralColor eval(Point p, Vector v, Vector w0) const = 0;

    virtual std::string to_string() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);
};
