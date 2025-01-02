#pragma once

#include <limits>
#include <vector>
#include <stdexcept>
#include <optional>

#include "intersection/intersection.hpp"
#include "brdf/brdf.hpp"


class IntersectionObject : public Intersection
{
private:
    Vector _normal;
    BRDF _brdf;
    bool _is_entering;
    std::optional<ColorRGB> _color_texture;
    double _u, _v;
public:

    IntersectionObject();
    IntersectionObject(double distance, Vector normal, Point intersection_point, BRDF brdf, Ray ray, bool is_entering = true);
    
    Vector get_normal() const;
    bool is_entering() const;

    void set_is_entering(const bool is_entering);
    void inverse_normal();
    void set_u_v(const double u, const double v);

    Color eval_brdf(Color light, Vector w_i, BRDFType type) const;
    BRDFType sample_ray(Ray& sampled_ray);

    bool operator==(const IntersectionObject i) const;

    friend std::ostream& operator<<(std::ostream& os, const IntersectionObject& i);

    std::string to_string() const;

};
