#pragma once

#include "geometry/geometry.hpp"

class Plane : Geometry
{
private:
    Vector _normal;
    Point _point;
    double _d;

public:
    Plane(Vector normal, Point point);
    Plane(Point p1, Point p2, Point p3);

    Point get_point() const;

    Vector get_normal() const;
    
    double implicit(Point x) const override;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const override;
};
