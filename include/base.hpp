/**
 * @file base.hpp
 * @brief Defines a base of R^3 and a center point.
 * @authors Davidjmz12 DavidTizne
 * @date 18/09/2024
 *
 * This file contains the definition of the Base class, which represents
 * a base in R^3.
*/
#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

#include "linear_map.hpp"
#include "matrix.hpp"

class Linear_Map;

/**
* @brief The class that represents a base with a point
*       of reference and three axis.
*/
class Base {

private:

    Matrix4x4 matrix;
    Matrix4x4 matrix_inverse;

public:

    Geometric center,x,y,z;
    
    /**
    * @brief Creates a base with center p and axis i,j,k.
    * @param p The referrence point of the base.
    * @param i The first vector of the base.
    * @param j The second vector of the base.
    * @param k The third vector of tha base.
    */
    Base(Geometric p, Geometric i, Geometric j, Geometric k);

    /**
    * @brief Method that gives the canionic base.
    * @return The canonic_base.
    */     
    static Base canonic_base();

    /**
    * @brief Method that gives the point in a basis.
    * @param x The coordinates of the x-canonical vector.
    * @param y The coordinates of the y-canonical vector.
    * @param z The coordinates of the z-canonical vector.
    * @return The coordinates of the point in the base-axis.
    */  
    Geometric coord_from_canonical(Geometric g) const;

    /**
    * @brief Method that gives the point in a basis.
    * @param x The coordinates of the x-basis vector.
    * @param y The coordinates of the y-basis vector.
    * @param z The coordinates of the z-basis vector.
    * @return The point with the coordinates (x,y,z).
    */        
    Geometric coord_into_canonical(Geometric g) const;

    /**
    * @brief Method that gives the matrix of this base.
    * @return the linear transformation of that matrix.
    */       
    Linear_Map canonical_to_base() const;

    /**
    * @brief An operator to print a base.
    * @param b the base to be printed.
    * @param os the output stream.
    * @return the resultant output stream with the printed base.
    */
    friend std::ostream& operator<<(std::ostream& os, const Base& b);

    /**
    * @brief An operator to check if two bases are the same.
    * @param b the second base.
    * @return True if the bases are equal. False otherwise.
    */
    bool operator==(Base b);
        
};

#endif