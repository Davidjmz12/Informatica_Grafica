
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "spatial_element/vector.hpp"
#include "spatial_element/point.hpp"
#include "properties/property.hpp"


class Intersection
{
private:
    double _distance;
    Vector _normal;
    Point _point;
    Property _properties;
    Vector _origin;

public:

    Intersection();
    Intersection(double distance, Vector normal, Point point, Property properties, Vector origin);
    Point get_point() const;
    double get_distance() const;
    Vector get_normal() const;
    Property get_properties() const;
    Vector get_origin() const;

    static Intersection min(std::vector<Intersection> intersections);
    bool operator<(const Intersection i) const;
    bool operator>(const Intersection i) const;
    bool operator==(const Intersection i) const;
    friend std::ostream& operator<<(std::ostream& os, const Intersection& i);
    
};
