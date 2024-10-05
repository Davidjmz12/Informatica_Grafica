
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "spatial_element/vector.hpp"
#include "spatial_element/point.hpp"


class Intersection
{
private:
    float _distance;
    Vector _normal;
    Point _point;

public:
    Intersection();
    Intersection(float distance, Vector normal, Point point);
    
    Point get_point() const;
    float distance() const;
    Vector get_normal() const;
    Intersection min(std::vector<Intersection> intersections) const;

    bool operator==(const Intersection i) const;
    friend std::ostream& operator<<(std::ostream& os, const Intersection& i);
};
