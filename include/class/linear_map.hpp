/**
 * @file linear_map.hpp
 * @brief Defines a linear map.
 *
 * This file contains the definition of the Geometric class, which represents
 * points and vectors with 3 components.
*/

#ifndef LINEAR_MAP
#define LINEAR_MAP

#include "geometric.hpp"
#include "base.hpp"
#include "math.h"

class Base;

class Linear_Map {
    private:
        float matrix[4][4];
        
    public:
        Linear_Map(float const matrix[4][4]);
        
        static Linear_Map change_basis(Base b1, Base b2);
        static Linear_Map rotation(Geometric axis, float angle);
        static Linear_Map scale(float lambda[3]);
        static Linear_Map translation(float v[3]);
        
        Linear_Map inverse() const;

        Linear_Map operator*(Linear_Map l) const;
        Geometric operator*(Geometric g) const;
};

#endif