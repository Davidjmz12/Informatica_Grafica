
#pragma once

#include <limits>

#include "geometric.hpp"


class Intersection
{
private:
    float _distance;
    Geometric _normal;
    Geometric _point;

public:
    Intersection();
    Intersection(float distance, Geometric normal, Geometric point);
    
    Geometric point() const;
    float distance() const;
    Geometric normal() const;
};
