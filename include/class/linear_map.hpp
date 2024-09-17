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
#include "matrix.hpp"
#include "math.h"

class Base;

/**
* @brief A class for representing linear maps.
*/
class Linear_Map {
    private:
        Matrix4x4 matrix;
        
    public:
        /**
        * @brief Method that creates a linear map given a Matrix4x4.
        * @param matrix The matrix of the transformation.
        */
        Linear_Map(Matrix4x4 M);

        /**
        * @brief Method that creates a linear map given an array.
        * @param matrix The matrix of the transformation.
        */
        Linear_Map(float M[4][4]);
        
        /**
        * @brief A method that creates a linear map to make a
        *   change of bases.
        * @param b1 The original base.
        * @param b2 The second base.
        * @return The linear map for changing from the base b1
        *   to the base b2
        */
        static Linear_Map change_basis(Base b1, Base b2);

        /**
        * @brief A method that creates a linear map to make a
        *   rotation.
        * @param axis The axis of the rotation.
        * @param angle The angle of the rotation.
        * @return The linear map of the rotation around axis with
        *   a determined angle.
        */
        static Linear_Map rotation(Geometric axis, float angle);

        /**
        * @brief A method that creates a linear map to make a
        *   scale.
        * @param lambda The scaled factor for each axis.
        * @return The linear map of the scale.
        */
        static Linear_Map scale(float lambda[3]);

        /**
        * @brief A method that creates a linear map to make a
        *   translation.
        * @param v The translation for each axis.
        * @return The linear map of the translation.
        * @throw std::invalid_argument if v is not a vector.
        */
        static Linear_Map translation(Geometric v);

        /**
        * @brief A method that gives the identity map.
        * @return A indentity map.
        */
        static Linear_Map identity();
        
        /**
        * @brief A method that computes the inverse linear map.
        * @return The inverse linear map.
        */
        Linear_Map inverse() const;

        /**
        * @brief A methode that redefines the product operator between
        *   linear maps
        * @param l The second linear map.
        * @return The linear map result of the composition of the
        *   two linear maps. The first linear map applied is l.
        */
        Linear_Map operator*(Linear_Map l) const;

        /**
        * @brief A method that redefines the product operator between
        *   a linear map and a geometric.
        * @param g The geometric which is going to be transformed.
        * @return The geometric result of apply the linear map to
        *   the geometric.
        */
        Geometric operator*(Geometric g) const;

        /**
        * @brief A method that redefines the equality operator between
        *   linear maps.
        * @param l The second linear map.
        * @return True if the matrices of both linear maps are identical.
        *   False otherwise.
        */
        bool operator==(Linear_Map l) const;

        friend std::ostream& operator<<(std::ostream& os,const Linear_Map& g);
};

#endif