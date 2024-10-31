
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
    Property _properties;
    
public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point point, Property properties, Vector origin);
    
    Vector get_normal() const;
    Property get_properties() const;

    SpectralColor evalRenderEquation(SpectralColor power_light, Point point_light) const;

    bool operator==(const IntersectionObject i) const;
    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);
    
};
