#pragma once

#include <limits>
#include <vector>
#include <stdexcept>

#include "intersection/intersection.hpp"
#include "properties/property.hpp"


class IntersectionObject : public Intersection
{
private:
    Vector _normal;
    Property _properties;
    
public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point intersection_point, Property properties, Ray ray);
    
    Vector get_normal() const;
    Property get_properties() const;

    SpectralColor evalRenderEquation(SpectralColor power_light, Point point_light) const;

    bool operator==(const IntersectionObject i) const;
    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);

    SpectralColor eval_brdf(Vector w_i) const;
    bool sample_ray(Ray& sampled_ray) const;
};
