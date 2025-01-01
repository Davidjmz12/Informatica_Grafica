#pragma once

#include "color/color.hpp"

class Texture {
public:
    virtual Color get_color(double u, double v) const = 0;
};