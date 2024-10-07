/**
 * @file point.hpp
 * @brief Defines points.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the definition of the Point
 * class, which represents points with 3 components.
*/

#pragma once

#include <spatial_element/spatial_element.hpp>
#include <spatial_element/vector.hpp>

class Vector;

class Point : public SpatialElement
{
public:
    Point(double x, double y, double z);

    explicit Point(const Vector v);

    explicit Point(SpatialElement* s);

    Point();

    bool is_point() const override;

    Point operator+(const Vector v) const;

    Point operator-(const Vector v) const;

    Vector operator-(const Point p) const;

    bool operator==(const Point v) const;

    std::string to_string() const;
};
