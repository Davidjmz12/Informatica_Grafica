#pragma once

#include <vector>
#include <stdexcept>

#include "global_config/constants.hpp"
#include "spatial_element/vector.hpp"

class Intersection
{
protected:
    double _distance;
    Vector _origin;

public:
    Intersection(double distance, Vector origin);

    Intersection();
    
    double get_distance() const;
    Vector get_origin() const;

    bool operator<(const Intersection& i) const;
    bool operator>(const Intersection& i) const;
};