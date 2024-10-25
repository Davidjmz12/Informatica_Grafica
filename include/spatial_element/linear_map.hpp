/**
 * @file linear_map.hpp
 * @brief Defines a linear map.
 *
 * This file contains the definition of the LinearMap class,
 * which represents linear mappings.
*/

#pragma once

#include <iostream>

#include "spatial_element/base.hpp"
#include "spatial_element/matrix.hpp"

class Base;

/**
* @brief A class for representing linear maps.
*/
class LinearMap {
    private:
        Matrix4x4 matrix;
        
    public:
        LinearMap();
        
        /**
        * @brief Method that creates a linear map given a Matrix4x4.
        * @param matrix The matrix of the transformation.
        */
        LinearMap(Matrix4x4 M);

        /**
        * @brief Method that creates a linear map given an array.
        * @param matrix The matrix of the transformation.
        */
        LinearMap(double M[4][4]);
        
        /**
        * @brief A method that creates a linear map to make a
        *   change of bases.
        * @param b1 The original base.
        * @param b2 The second base.
        * @return The linear map for changing from the base b1
        *   to the base b2
        */
        static LinearMap change_basis(Base b1, Base b2);

        /**
        * @brief A method that creates a linear map to make a
        *   rotation.
        * @param axis The axis of the rotation.
        * @param angle The angle of the rotation.
        * @return The linear map of the rotation around axis with
        *   a determined angle.
        */
        static LinearMap rotation(Vector axis, double angle);

        /**
        * @brief A method that creates a linear map to make a
        *   scale.
        * @param lambda The scaled factor for each axis.
        * @return The linear map of the scale.
        */
        static LinearMap scale(double lambda[3]);

        /**
        * @brief A method that creates a linear map to make a
        *   translation.
        * @param v The translation for each axis.
        * @return The linear map of the translation.
        * @throw std::invalid_argument if v is not a vector.
        */
        static LinearMap translation(Vector v);

        /**
        * @brief A method that gives the identity map.
        * @return A indentity map.
        */
        static LinearMap identity();
        
        /**
        * @brief A method that computes the inverse linear map.
        * @return The inverse linear map.
        */
        LinearMap inverse() const;

        /**
        * @brief A methode that redefines the product operator between
        *   linear maps
        * @param l The second linear map.
        * @return The linear map result of the composition of the
        *   two linear maps. The first linear map applied is l.
        */
        LinearMap operator*(LinearMap l) const;

        /**
        * @brief A method that redefines the product operator between
        *   a linear map and a spatial element.
        * @param s The spatial element which is going to be transformed.
        * @return The spatial element result of apply the linear map to
        *   the spatial element.
        */
        SpatialElement* operator*(const SpatialElement* s) const;

        /**
        * @brief A method that redefines the equality operator between
        *   linear maps.
        * @param l The second linear map.
        * @return True if the matrices of both linear maps are identical.
        *   False otherwise.
        */
        bool operator==(LinearMap l) const;

        friend std::ostream& operator<<(std::ostream& os,const LinearMap& g);
};

