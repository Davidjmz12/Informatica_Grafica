/**
 * @file spatial_element.cpp
 * @brief Implements points and vectors.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the implementation of the spatialElement
 * class, which represents points and vectors with 3 components.
*/

#include "spatial_element/spatial_element.hpp"

SpatialElement::SpatialElement(double x, double y, double z)
    : _coordinates(std::array<double,3>{x,y,z})
{}

double SpatialElement::operator[](int index) const
{
    if (index < 0 || index > 2)
        throw std::out_of_range("Index must be between 0-2");

    return (*this)[index];
}

std::ostream&  operator<<(std::ostream& os, const SpatialElement& s) 
{
    os  <<  "(" <<  std::setprecision(6) << s[0] << "," <<
                    std::setprecision(6) << s[1] << "," <<
                    std::setprecision(6) << s[2] << ")";
    return os;
}
