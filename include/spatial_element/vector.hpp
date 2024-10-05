/**
 * @file vector.hpp
 * @brief Defines vectors.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the definition of the Vector
 * class, which represents vectors with 3 components.
*/

#pragma once

#include "spatial_element/spatial_element.hpp"
#include "spatial_element/point.hpp"

class Point;

class Vector : public SpatialElement
{
public:
    Vector(double x, double y, double z);

    explicit Vector(Point p);

    explicit Vector(SpatialElement* s);

    Vector();

    bool is_vector() const override;

    double norm() const;

    Vector normalize() const;

    double dot(const Vector* v) const;

    Vector cross(const Vector* v) const;

    bool linearly_dependent(const Vector* v) const;

    bool is_base(const Vector* v1, const Vector* v2) const;

    Vector operator+(const Vector v) const;

    Point operator+(const Point p) const;

    Vector operator-(const Vector v) const;

    Vector operator*(double scalar) const;

    Vector operator/(double scalar) const;

    bool operator==(const Vector v) const;
};
