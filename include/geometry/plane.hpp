#pragma once

#include "geometry/geometry.hpp"

class Plane : public Geometry
{
private:
    Vector _normal;
    Point _point;
public:
    Plane(Point point, Vector normal);
    Plane(Point p1, Point p2, Point p3);

    Point get_point() const;

    Vector get_normal() const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};
