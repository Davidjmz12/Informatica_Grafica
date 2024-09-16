#ifndef MATRIX_HPP
#define MATRIX_HPP

const int SIZE = 4;
const float threshold = 10e-6;

/**
* @brief Computes A*B and store the result in Result.
* @param A First matrix.
* @param B Second matrix.
* @param Result The resultant matrix A*B.
*/
void matrix_multiplication(float const A[SIZE][SIZE], float const B[SIZE][SIZE], float Result[SIZE][SIZE]);

/**
* @brief Computes the inverse of a matrix 4x4.
* @param A The matrix to inverse.
* @param Result The resultant matrix A^-1.
*/
void matrix_inverse(float const A[SIZE][SIZE], float Result[SIZE][SIZE]);

/**
* @brief Computes the determinant of a matrix 4x4.
* @param A The matrix that is going to be used.
* @param Result The determinant of A.
*/
float matrix_determinant(float const A[SIZE][SIZE]);

/**
* @brief Prints the matrix A.
* @param A The matrix to be printed.
*/
void printMatrix(float A[SIZE][SIZE]);

#endif