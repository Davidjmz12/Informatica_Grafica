#pragma once

#include <vector>
#include <stdexcept>

#include "global_config/constants.hpp"
#include "spatial_element/vector.hpp"
#include "scene/ray.hpp"

class Intersection
{
protected:
    double _distance;
    Point _intersection_point;
    Ray _ray;
public:
    Intersection(double distance, Point intersection_point, Ray ray);

    Intersection();
    
    double get_distance() const;
    Vector get_dir_int() const;
    Point get_int_point() const;
    Point get_origin() const;
    double get_refraction_coefficient() const;
    Ray get_ray() const;

    bool operator<(const Intersection& i) const;
    bool operator>(const Intersection& i) const;
};