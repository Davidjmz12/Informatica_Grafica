#pragma once

#include "geometry/disk.hpp"
#include "linear_map.hpp"

class Cone : public Geometry
{
private:
    Point _vertex;
    Vector _axe;
    double _height;
    double _radius;
    double _max_distance;
    Disk _base;

    LinearMap _centering;
    LinearMap _centering_inverse;

public:
    Cone(Point vertex, Vector axe, double height, double radius, Property properties);

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const override;

    std::string to_string() const override;
};
