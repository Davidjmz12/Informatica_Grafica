#pragma once

#include "spatial_element/point.hpp"
#include "spatial_element/vector.hpp"

class Ray
{
private:
    Point _point;
    Vector _direction;
    double _refraction_coefficient{};
    
public:
    Ray();
    Ray(const Point& point, const Vector& direction, double refraction_coefficient = 1.0);
    [[nodiscard]] Point evaluate(double t) const;
    [[nodiscard]] Point get_point() const;
    [[nodiscard]] Vector get_direction() const;
    [[nodiscard]] double get_refraction_coefficient() const;

    friend std::ostream& operator<<(std::ostream& os, const Ray& r);

    [[nodiscard]] std::string to_string() const;
};
