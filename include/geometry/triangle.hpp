#pragma once

#include "geometry/geometry.hpp"
#include "geometry/plane.hpp"

class Triangle : public Geometry
{
private:
    Point _v0;
    Point _v1;
    Point _v2;

    bool point_inside_triangle(Point p) const;
public:

    Triangle(Point v0, Point v1, Point v2);

    Vector get_normal() const;
    Plane plane() const ;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};