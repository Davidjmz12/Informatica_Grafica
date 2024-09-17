/**
 * @file matrix.hpp
 * @brief Defines a matrix 4x4
 *
 * This file contains the definition of the Matrix4x4 class, which represents
 * a 4x4 real matrix.
*/
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

const float threshold = 10e-6; // Under this number, it is considered as 0.

class Matrix4x4 {
    private:
        float matrix[4][4]; // Matrix attribute
        
    public:

    /**
    * @brief Basic constructor of a matrix 4x4.
    */
    Matrix4x4(float const m[4][4]);

    /**
    * @brief Access the (i,j) term of the matrix.
    * @param i the i-index.
    * @param j the j-index.
    * @throw std::invalid_argument if index out of range.
    * @return the (i,j) index of the matrix, M[i,j]
    */
    float get(int i, int j) const;

    /**
    * @brief Computes the inverse of the matrix 4x4.
    * @return the inversed matrix.
    */
    Matrix4x4 inverse() const;

    /**
    * @brief Computes the determinant of the matrix.
    * @return the determinant.
    */
    float determinant() const;

    /**
    * @brief Prints the matrix.
    * @param M The matrix to be printed.
    * @param os the output stream where to print.
    * @return the output stream with the printed matrix.
    */
    friend std::ostream& operator<<(std::ostream& os,const Matrix4x4& M);

    /**
    * @brief Computes a the multiplication of the matrix by M.
    * @param M Second matrix.
    * @return Result of multiplicate the matrix by M.
    */
    Matrix4x4 operator*(Matrix4x4& M) const;

};


#endif