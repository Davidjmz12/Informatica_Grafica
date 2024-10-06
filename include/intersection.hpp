
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "spatial_element/vector.hpp"
#include "spatial_element/point.hpp"


class Intersection
{
private:
    double _distance;
    Vector _normal;
    Point _point;

public:

    Intersection();
    Intersection(double distance, Vector normal, Point point);
    
    Point get_point() const;
    double get_distance() const;
    Vector get_normal() const;

    static Intersection min(std::vector<Intersection> intersections);
    bool operator==(const Intersection i) const;
    friend std::ostream& operator<<(std::ostream& os, const Intersection& i);
    
};
