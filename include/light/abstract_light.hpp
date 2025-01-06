#pragma once

#include "color/color.hpp"
#include "scene/ray.hpp"

class AbstractLight
{
private:

public:
    virtual double luminance_max() const = 0;

    virtual Ray sample_ray() const = 0;

};