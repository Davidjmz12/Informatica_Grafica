/**
 * @file base.hpp
 * @brief Defines a base of R^3 and a center point.
 *
 * This file contains the definition of the Base class, which represents
 * a base in R^3.
*/
#ifndef BASE_HPP
#define BASE_HPP

#include "geometric.hpp"
#include "linear_map.hpp"

class Linear_Map;

/**
* @brief The class that represents a base with a point
*       of reference and three axis.
*/
class Base {

private:
    float matrix[4][4];
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
    * @param x The coordinates of the x-basis vector.
    * @param y The coordinates of the y-basis vector.
    * @param z The coordinates of the z-basis bector.
    * @return The point with the coordinates (x,y,z).
    */        
    Geometric point(float x, float y, float z) const;


    /**
    * @brief Method that gives the matrix of this base.
    * @return the linear transformation of that matrix.
    */       
    Linear_Map matrix_lt() const;


    /**
    * @brief An operator to print a base.
    * @param b the base to be printed.
    * @param os the output stream.
    * @return the resultant output stream with the printed base.
    */
    friend std::ostream& operator<<(std::ostream& os, const Base& b);
        
};

#endif