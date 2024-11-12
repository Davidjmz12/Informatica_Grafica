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

SpatialElement::SpatialElement(double x, double y, double z, double type)
    : _coordinates(std::array<double,4>{x,y,z,type})
{}

double SpatialElement::operator[](const int index) const
{
    if (index < 0 || index > 3)
        throw std::out_of_range("Index must be between 0-2");

    return this->_coordinates[index];
}

void SpatialElement::set_x(const double x)
{
    this->_coordinates[0] = x;
}

void SpatialElement::set_y(const double y)
{
    this->_coordinates[1] = y;
}

void SpatialElement::set_z(const double z)
{
    this->_coordinates[2] = z;
}


std::ostream&  operator<<(std::ostream& os, const SpatialElement& s) 
{
    os  <<  s.to_string();
    return os;
}

bool SpatialElement::is_point() const
{
    return false;
}

bool SpatialElement::is_vector() const
{
    return false;
}
