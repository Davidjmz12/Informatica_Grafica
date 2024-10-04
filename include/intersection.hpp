
#pragma once

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
    
    bool operator=(Intersection i) const;
};
