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

public:

    Point _center;
    Vector _i, _j, _k;
    
    /**
    * @brief Creates a base with center p and axis i,j,k.
    * @param p The reference point of the base.
    * @param i The first vector of the base.
    * @param j The second vector of the base.
    * @param k The third vector of tha base.
    */
    Base(const Point& p, const Vector& i, const Vector& j, const Vector& k);

    /**
    * @brief Method that gives the canonic base.
    * @return The canonic_base.
    */     
    static Base canonic_base();

    static Base complete_base_k(const Point& c, const Vector& v);

    static Vector sample_hemisphere(const Vector& normal, const Point& p);

    /**
    * @brief Method that gives the point in a basis.
    * @param s Point with coordinates (x,y,z) in canonical base.
    * @return The coordinates of the point in the base-axis.
    */  
    SpatialElement* coord_from_canonical(const SpatialElement* s) const;

    /**
    * @brief Method that gives the point in a basis.
    * @param s Point with coordinates (x,y,z) in this base.
    * @return The point with the coordinates (x,y,z).
    */        
    SpatialElement* coord_into_canonical(const SpatialElement* s) const;

    /**
    * @brief Method that gives the matrix of this base.
    * @return the linear transformation of that matrix.
    */       
    [[nodiscard]] LinearMap canonical_to_base() const;

    
    [[nodiscard]] Point get_center() const;

    [[nodiscard]] Base normalize() const;

    /**
    * @brief An operator to print a base.
    * @param b the base to be printed.
    * @param os the output stream.
    * @return the resultant output stream with the printed base.
    */
    friend std::ostream& operator<<(std::ostream& os, const Base& b);

    [[nodiscard]] std::string to_string() const;

    Vector operator[](int i) const;

    /**
    * @brief An operator to check if two bases are the same.
    * @param b the second base.
    * @return True if the bases are equal. False otherwise.
    */
    bool operator==(const Base& b) const;



        
};
