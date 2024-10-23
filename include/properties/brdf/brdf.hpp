#pragma once

#include "spatial_element/point.hpp"
#include "spatial_element/vector.hpp"
#include "color.hpp"

class BRDF {
public:
    virtual Color eval(Point p, Vector v, Vector w0) const = 0;
};
