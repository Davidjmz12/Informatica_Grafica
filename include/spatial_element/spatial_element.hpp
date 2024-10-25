/**
 * @file spatial_element.hpp
 * @brief Defines points and vectors.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the definition of the spatialElement
 * class, which represents points and vectors with 3 components.
*/

#pragma once

#include <array>
#include <stdexcept>
#include <iomanip>

#include "global_config/constants.hpp"

class SpatialElement
{
protected:
    std::array<double,4> _coordinates;

public:
    SpatialElement(double x, double y, double z, double type);

    double operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const SpatialElement& s);

    virtual bool is_point() const;

    virtual bool is_vector() const;

    virtual std::string to_string() const = 0;
};
