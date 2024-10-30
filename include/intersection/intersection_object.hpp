
#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "intersection/intersection.hpp"
#include "spatial_element/vector.hpp"
#include "spatial_element/point.hpp"
#include "properties/property.hpp"


class IntersectionObject : public Intersection
{
private:
    Vector _normal;
    Point _point;
    Property _properties;
    Vector _origin;

public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point point, Property properties, Vector origin);
    Point get_point() const;

    Vector get_normal() const;
    Property get_properties() const;
    Vector get_origin() const;

    bool operator==(const IntersectionObject i) const;
    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);
    
};
