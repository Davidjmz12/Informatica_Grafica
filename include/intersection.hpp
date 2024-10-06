
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "geometric.hpp"


class Intersection
{
private:
    double _distance;
    Geometric _normal;
    Geometric _point;

public:
    Intersection();
    Intersection(double distance, Geometric normal, Geometric point);
    
    Geometric point() const;
    double distance() const;
    Geometric normal() const;
    static Intersection min(std::vector<Intersection> intersections);
};
