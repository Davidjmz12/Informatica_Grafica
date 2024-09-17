#include <iostream>
#include <iomanip>

#include "matrix.hpp"

void matrix_multiplication(float const A[SIZE][SIZE], float const B[SIZE][SIZE], float Result[SIZE][SIZE])
{
	for(int row=0; row<SIZE; row++){
        for(int column=0; column<SIZE; column++){
            float aux = 0;
            for(int k=0; k<SIZE; k++){
                aux += A[row][k]*B[k][column];
            }
            Result[row][column] = aux > threshold ? aux : 0;
        }
	}
}

void printMatrix(float A[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << std::setw(10) << std::setprecision(5) << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


float determinant3x3(float mat[3][3]) {
    float det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
                - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
                + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    return det > threshold ? det : 0;
}

void getCofactor(float const mat[SIZE][SIZE], float temp[3][3], int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == 3) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(float const mat[SIZE][SIZE], float adj[SIZE][SIZE]) {
    if (SIZE == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    float temp[3][3];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            getCofactor(mat, temp, i, j);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant3x3(temp);
        }
    }
}

float matrix_determinant(float const A[SIZE][SIZE])
{
    float det = 0.0;
    float temp[3][3];
    int sign = 1;

    for (int f = 0; f < SIZE; f++) {
        getCofactor(A, temp, 0, f);
        det += sign * A[0][f] * determinant3x3(temp);
        sign = -sign;
    }

    return det > threshold ? det : 0;
}

void matrix_inverse(float const A[SIZE][SIZE], float Result[SIZE][SIZE])
{
    //Compute the determinant
    float det = matrix_determinant(A);
    if (det == 0)
        throw std::invalid_argument("Matrix cannot have determinant 0.");

    //Compute of the adjoint matrix
    float adj[SIZE][SIZE];
    adjoint(A, adj);

    //Compute the inverse matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Result[i][j] = adj[i][j] / det > threshold ? adj[i][j] / det : 0;
        }
    }   
}