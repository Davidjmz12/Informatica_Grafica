/**
 * @file base.hpp
 * @brief Defines a base of R^3 and a center point.
 * @authors Davidjmz12 DavidTizne
 * @date 18/09/2024
 *
 * This file contains the definition of the Base class, which represents
 * a base in R^3.
*/

#pragma once

#include <iostream>

#include "spatial_element/linear_map.hpp"
#include "spatial_element/matrix.hpp"

class LinearMap;

/**
* @brief The class that represents a base with a point
*       of reference and three axis.
*/
class Base {

private:

    Matrix4x4 _matrix;
    Matrix4x4 _matrix_inverse;

public:

    Point _center;
    Vector _i, _j, _k;
    
    /**
    * @brief Creates a base with center p and axis i,j,k.
    * @param p The referrence point of the base.
    * @param i The first vector of the base.
    * @param j The second vector of the base.
    * @param k The third vector of tha base.
    */
    Base(Point p, Vector i, Vector j, Vector k);

    /**
    * @brief Method that gives the canionic base.
    * @return The canonic_base.
    */     
    static Base canonic_base();

    /**
    * @brief Method that gives the point in a basis.
    * @param g Point with coordinates (x,y,z) in cannonical base.
    * @return The coordinates of the point in the base-axis.
    */  
    SpatialElement* coord_from_canonical(const SpatialElement* s) const;

    /**
    * @brief Method that gives the point in a basis.
    * @param g Point with coordinates (x,y,z) in this base.
    * @return The point with the coordinates (x,y,z).
    */        
    SpatialElement* coord_into_canonical(const SpatialElement* s) const;

    /**
    * @brief Method that gives the matrix of this base.
    * @return the linear transformation of that matrix.
    */       
    LinearMap canonical_to_base() const;

    
    Point get_center() const;

    Base normalize() const;

    /**
    * @brief An operator to print a base.
    * @param b the base to be printed.
    * @param os the output stream.
    * @return the resultant output stream with the printed base.
    */
    friend std::ostream& operator<<(std::ostream& os, const Base& b);

    Vector operator[](int i) const;

    /**
    * @brief An operator to check if two bases are the same.
    * @param b the second base.
    * @return True if the bases are equal. False otherwise.
    */
    bool operator==(Base b) const;



        
};