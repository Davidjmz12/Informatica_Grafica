#pragma once

#include "intersection/intersection_object.hpp"

class Ray
{
private:
    Point _point;
    Vector _direction;
    double _refraction_coefficient;
    
public:
    Ray();
    Ray(Point point, Vector direction, double refraction_coefficient = 1.0);
    Point evaluate(double t) const;
    Point get_point() const;
    Vector get_direction() const;
    double get_refraction_coefficient() const;

    friend std::ostream& operator<<(std::ostream& os, const Ray& r);

    std::string to_string() const;
};
