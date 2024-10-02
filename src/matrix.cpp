/**
 * @file matrix.cpp
 * @brief Implementation of the matrix header.
 * @authors DavidJimenez DavidTizne
 * @date 18/09/2024
 * @see matrix.hpp for more information.
 * This file contains the implementation of a 4x4 real matrix.
*/


#include <iostream>
#include <iomanip>
#include <math.h>

#include "matrix.hpp"

float determinant3x3(float mat[3][3]) {
    float det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
                - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
                + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    return det;
}

void getCofactor(float const mat[4][4], float temp[3][3], int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
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

void adjoint(float const mat[4][4], float adj[4][4]) {

    int sign = 1;
    float temp[3][3];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            getCofactor(mat, temp, i, j);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant3x3(temp);
        }
    }
}

Matrix4x4::Matrix4x4() {}

Matrix4x4::Matrix4x4(float const m[4][4])
{
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++){
            this->matrix[row][col] = m[row][col];
        }
    }
}

Matrix4x4::Matrix4x4(float const m[3][3])
{
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            this->matrix[row][col] = m[row][col];
        }
    }

    for (int i = 0; i < 3; i++){
        this->matrix[3][i] = 0;
        this->matrix[i][3] = 0;
    }

    this->matrix[3][3] = 1;
}

Matrix4x4 Matrix4x4::identity()
{
    float v[4][4] = {{1,0,0,0},
                     {0,1,0,0},
                     {0,0,1,0},
                     {0,0,0,1}};
    return Matrix4x4(v);
}

float Matrix4x4::get(int i, int j) const
{
    if (i < 0 || i > 4 || j < 0 || j > 4)
        throw std::invalid_argument("Index out of range.");
    return this->matrix[i][j];
}

Matrix4x4 Matrix4x4::inverse() const
{
    //Compute the determinant
    float det = this->determinant();
    if (det == 0)
        throw std::invalid_argument("Matrix cannot have determinant 0.");

    //Compute of the adjoint matrix
    float adj[4][4];
    adjoint(this->matrix, adj);

    //Compute the inverse matrix
    float res[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = adj[i][j] / det;
        }
    } 

    return Matrix4x4(res);
}

float Matrix4x4::determinant() const
{
    float det = 0.0;
    float temp[3][3];
    int sign = 1;

    for (int f = 0; f < 4; f++) {
        getCofactor(this->matrix, temp, 0, f);
        det += sign * this->matrix[0][f] * determinant3x3(temp);
        sign = -sign;
    }

    return det;
}

std::ostream& operator<<(std::ostream& os,const Matrix4x4 M)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << std::setw(10) << std::setprecision(5) << M.get(i,j) << " ";
        }
        if(i<3)
            os << std::endl;
    }
    return os;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 M) const
{
    float result [4][4];

	for(int row=0; row<4; row++){
        for(int column=0; column<4; column++){
            float aux = 0;
            for(int col=0; col<4; col++){
                aux += this->get(row,col)*M.get(col,column);
            }
            result[row][column] = aux;
        }
	}

    return Matrix4x4(result);
}

Geometric Matrix4x4::operator*(Geometric g) const
{
    float res[4];
    float aux = 0;

    //Multiply the matrix and the vector
    for(int row=0; row<4; row++){
        aux = 0;
        for(int col=0; col<4; col++){
            aux += this->get(row,col) * g[col];
        }
        res[row] = aux;
	}

    //Return the correct type of geometric
    if (g.is_point()) {
        return Geometric::point(res[0], res[1], res[2]);
    } else {
        return Geometric::vector(res[0], res[1], res[2]);
    }
}

Matrix4x4 Matrix4x4::operator*(float f) const
{
    float res[3][3];
    float aux = 0;

    //Multiply the matrix and the vector
    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            res[row][col] = this->get(row,col) * f;
        }
	}
    
    return Matrix4x4(res);
}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 M) const
{
    float res[3][3];
    float aux = 0;

    //Multiply the matrix and the vector
    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            res[row][col] = this->get(row,col) + M.get(row,col);
        }
	}  

    return Matrix4x4(res); 
}

bool Matrix4x4::operator==(Matrix4x4 const M) const
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!eqFloat(this->get(i,j),M.get(i,j)))
                return false;
        }
    }
    return true;
}

