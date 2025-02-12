/**
 * @file matrix.hpp
 * @brief Defines a matrix 4x4
 *
 * This file contains the definition of the Matrix4x4 class, which represents
 * a 4x4 real matrix.
*/
#pragma once

#include <iostream>

#include "spatial_element/spatial_element.hpp"
#include "spatial_element/vector.hpp"
#include "spatial_element/point.hpp"

class Matrix4x4 {
    private:
        double matrix[4][4]; // Matrix attribute
        
    public:

    /**
    * @brief Basic constructor of a matrix 4x4.
    */
    Matrix4x4();

    /**
    * @brief Creates a matrix 4x4 putting the matrix m at
    *   the beggining and completing the last row and colum
    *   by the canonical vector
    */
    Matrix4x4(double const m[3][3]);

    /**
    * @brief Basic constructor of a matrix 4x4.
    */
    Matrix4x4(double const m[4][4]);

    /**
    * @brief Static method that gives the identity matrix.
    * @returns the identity matrix
    */
    static Matrix4x4 identity();

    /**
    * @brief Access the (i,j) term of the matrix.
    * @param i the i-index.
    * @param j the j-index.
    * @throw std::invalid_argument if index out of range.
    * @return the (i,j) index of the matrix, M[i,j]
    */
    double get(int i, int j) const;

    /**
    * @brief Computes the inverse of the matrix 4x4.
    * @return the inversed matrix.
    */
    Matrix4x4 inverse() const;

    /**
    * @brief Computes the determinant of the matrix.
    * @return the determinant.
    */
    double determinant() const;

    /**
    * @brief Computes the sum of the matrix by M.
    * @param M Second matrix.
    * @return Result of adding the matrix M.
    */
    Matrix4x4 operator+(Matrix4x4 M) const;

    /**
    * @brief Computes the multiplication of the matrix by M.
    * @param M Second matrix.
    * @return Result of multiplicate the matrix by M.
    */
    Matrix4x4 operator*(Matrix4x4 M) const;

    /**
    * @brief Computes the multiplication of the matrix by a spatial element (array 4x1).
    * @param s the spatial element to multiply with
    * @return Result of the product of the matrix by M.
    */
    SpatialElement* operator*(const SpatialElement* s) const;

    /**
    * @brief Computes the multiplication of the matrix by a double.
    * @param f the double of the multiplication
    * @return Result of the product of the matrix by f.
    */
    Matrix4x4 operator*(double f) const;


    /**
    * @brief A method that redefines the equality operator between matrices.
    * @param M Second matrix.
    * @return true if and only if both matrices are equal.
    */
    bool operator==(Matrix4x4 M) const;

    /**
    * @brief Prints the matrix.
    * @param M The matrix to be printed.
    * @param os the output stream where to print.
    * @return the output stream with the printed matrix.
    */
    friend std::ostream& operator<<(std::ostream& os,const Matrix4x4 M);

};
