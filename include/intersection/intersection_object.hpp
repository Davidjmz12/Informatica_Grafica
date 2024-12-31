#pragma once

#include <limits>
#include <vector>
#include <stdexcept>
#include <optional>

#include "intersection/intersection.hpp"
#include "properties/property.hpp"


class IntersectionObject : public Intersection
{
private:
    Vector _normal;
    Property _properties;
    bool _is_entering;
    std::optional<ColorRGB> _color_texture;
public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point intersection_point, Property properties, Ray ray, bool is_entering = true);
    
    Vector get_normal() const;
    Property get_properties() const;
    bool is_entering() const;

    void set_is_entering(const bool is_entering);
    void inverse_normal();
    void change_color(ColorRGB color);

    bool is_delta() const;

    Color eval_brdf(Color light, Vector w_i) const;
    bool sample_ray(Ray& sampled_ray);

    bool operator==(const IntersectionObject i) const;

    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);

    static IntersectionObject min(const std::vector<IntersectionObject>& intersections);

    std::string to_string() const;

};
