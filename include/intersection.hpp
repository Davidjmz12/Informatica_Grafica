
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

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
    Intersection min(std::vector<Intersection> intersections) const;

    bool operator==(const Intersection i) const;
    friend std::ostream& operator<<(std::ostream& os, const Intersection& i);
};
