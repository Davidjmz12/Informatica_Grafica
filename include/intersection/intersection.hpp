#pragma once

#include <vector>
#include <stdexcept>
#include <memory>

#include "global_config/constants.hpp"

class Intersection
{
protected:
    double _distance;

public:
    Intersection(double distance);
    
    double get_distance() const;

    static std::shared_ptr<Intersection> min(std::vector<std::shared_ptr<Intersection>> intersections);

    bool operator<(const Intersection& i) const;
    bool operator>(const Intersection& i) const;
};