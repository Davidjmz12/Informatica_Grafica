#pragma once

#include "spatialElement/point.hpp"
#include "color.hpp"

class BRDF {
public:
    virtual Color eval(Point p, Vector v, double d) = 0;
};
