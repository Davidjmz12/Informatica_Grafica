/**
 * @file geometric.hpp
 * @brief Defines points and vectors.
 *
 * This file contains the definition of the Geometric class, which represents
 * points and vectors with 3 components.
*/

#ifndef GEOMETRIC
#define GEOMETRIC

#include <iostream>
#include <array>

#include "constants.hpp"

/**
 * @brief A class for representing points and vectors with
 *        3 components.
 */
class Geometric
{
private:

    std::array<float,4> v; // Coordinates v[0-2] and type of geometric v[3].

    /**
    * @brief General constructor.
    * @throw std::invalid_argument if a3 != {0,1}
    */
    Geometric(float a0, float a1, float a2, float a3);

public:

    /**
    * @brief Returns a point with coordinates p.
    * @param x The coordinates of the x-axis
    * @param y The coordinates of the y-axis
    * @param z The coordinates of the z-axis
    * @return A point with coordinates p.
    */
    static Geometric point(float x, float y, float z);

    /**
    * @brief Returns the (0,0,0) point.
    * @return The zero point.
    */
    static Geometric point0();

    /**
    * @brief Returns the (0,0,0) vector.
    * @return The zero vector.
    */
    static Geometric vector0();

    /**
    * @brief Returns a vector with coordinates v.
    * @param x The coordinates of the x-axis
    * @param y The coordinates of the y-axis
    * @param z The coordinates of the z-axis
    * @return A vector with coordinates v.
    */
    static Geometric vector(float x, float y, float z);

    /**
    * @brief Checks if the geometric is a vector.
    * @return True if the geometric is a vector. False otherwise.
    */
    bool is_vector() const;

    /**
    * @brief Checks if the geometric is a point.
    * @return True if the geometric is a point. False otherwise.
    */
    bool is_point() const;

    /**
    * @brief Computes the Euclidean norm of the vector.
    * @return The Euclidean norm of the vector.
    * @throw std::invalid_argument if the geometric is a point.
    */
    float norm() const;

    /**
    * @brief Normalizes the vector.
    * @return The normalized vector.
    * @throw std::invalid_argument if the geometric is a point.
    * @throw std::runtime_error if the geometric is zero vector.
    */
    Geometric normalize() const;

    /**
    * @brief Computes the dot product of the vector and g.
    * @param g The second vector for doing the dot product.
    * @return The dot product of the geometric and g.
    * @throw std::invalid_argument if the geometric is a point.
    */
    float dot(Geometric const g) const;
    
    /**
    * @brief A method that computes the cross product of two geometrics.
    * @param g The second vector for doing the cross product.
    * @throw std::invalid_argument if any geometric is a point.
    * @return The cross product of both geometrics.
    */
    Geometric cross(Geometric const g) const;

    /**
    * @brief A method that computes if the vectors are linearly dependent.
    * @param g The second vector.
    * @throw std::invalid_argument if any geometric is not a vector.
    * @return True if both vectors are linearly dependent. False otherwise.
    */
    bool linearly_dependent(Geometric const g) const;

    /**
    * @brief A method that computes if three vectors are a base.
    * @param g1 The second vector.
    * @param g2 The third vector.
    * @throw std::invalid_argument if any geometric is not a point.
    * @return True if the three vectors are a base. False otherwise.
    */
    bool is_base(Geometric g1, Geometric g2) const;

    /**
    * @brief A method that computes the sum of two geometric.
    * @param g the geometric.
    * @return The sum of the two geometrics.
    * @throw std::invalid_argument if doing point + point.
    */
    Geometric operator+(Geometric const g) const;

    /**
    * @brief A method that computes the substraction of two geometric.
    * @param g the geometric.
    * @return The substraction of the two geometrics.
    * @throw std::invalid_argument if doing vector - point.
    */
    Geometric operator-(Geometric const g) const;

    /**
    * @brief A method that computes the multiplication of the geometric.
    *        by a scalar.
    * @param scalar scale factor.
    * @return The scaled geometric.
    * @throw std::invalid_argument if geometric is not a vector
    */
    Geometric operator*(float scalar) const;

    /**
    * @brief A method that computes the division of the geometric.
    *        by a scalar.
    * @param scalar scale factor.
    * @return The scaled geometric.
    * @throw std::runtime_error if scalar is zero.
    * @throw std::invalid_argument if geometric is not a vector
    */
    Geometric operator/(float scalar) const;

    /**
    * @brief An operator two compare two geometrics.
    * @param g the geometric to compare with.
    * @return true if and only if both geometrics are the same.
    */
    bool operator==(Geometric const g) const;

    /**
    * @brief An operator to print the geometric.
    * @param g the geometric to be printed.
    * @param os the output stream.
    * @return the resultant output stream with the printed geometric.
    */
    friend std::ostream& operator<<(std::ostream& os,const Geometric& g);


    float operator[](int index) const;

};

#endif