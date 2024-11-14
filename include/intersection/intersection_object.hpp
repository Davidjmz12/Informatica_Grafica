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
    bool _is_entering;
public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point intersection_point, Property properties, Ray ray, bool is_entering = true);
    
    Vector get_normal() const;
    Property get_properties() const;
    bool is_entering() const;

    bool is_delta() const;

    SpectralColor eval_brdf(SpectralColor light, Vector w_i) const;
    bool sample_ray(Ray& sampled_ray);

    bool operator==(const IntersectionObject i) const;

    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);

    std::string to_string() const;

};
