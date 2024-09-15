#include "linear_map.hpp"
// #include <lib/armadillo-14.0.2/armadillo>

const int N = 4;

void matrix_multiplication(float const A[N][N], float const B[N][N], float Resultado[N][N]) {
	for(int row=0;row<N;row++){
        for(int column=0;column<N;column++){
            float aux=0;
            for(int k=0;k<N;k++){
                aux += A[row][k]*B[k][column];
            }
            Resultado[row][column] = aux;
        }
	}
}

Linear_Map::Linear_Map(float const matrix[4][4]) {
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

Linear_Map change_basis(Base origin, Base b2) 
{
    return b2.matrix_lt().inverse() * origin.matrix_lt();
}

Linear_Map rotation(Geometric axis, float angle) 
{
    axis = axis.normalize();

    float matrix[4][4];

    matrix[0][0] = cos(angle) + pow(axis[0],2)*(1-cos(angle));
    matrix[0][1] = axis[0]*axis[1]*(1-cos(angle))-axis[2]*sin(angle);
    matrix[0][2] = axis[0]*axis[2]*(1-cos(angle))+axis[1]*sin(angle);
    matrix[0][3] = 0;

    matrix[1][0] = axis[1]*axis[0]*(1-cos(angle))+axis[2]*sin(angle);
    matrix[1][1] = cos(angle) + pow(axis[1],2)*(1-cos(angle));
    matrix[1][2] = axis[1]*axis[2]*(1-cos(angle))-axis[0]*sin(angle);
    matrix[1][3] = 0;

    matrix[2][0] = axis[2]*axis[0]*(1-cos(angle))-axis[1]*sin(angle);
    matrix[2][1] = axis[2]*axis[1]*(1-cos(angle))+axis[0]*sin(angle);
    matrix[2][2] = cos(angle) + pow(axis[2],2)*(1-cos(angle));
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

    return Linear_Map(matrix);
}

Linear_Map scale(float lambda[3]) 
{
    float matrix[4][4] =    {   {lambda[0], 0, 0, 0},
                                {0, lambda[1], 0, 0},
                                {0, 0, lambda[2], 0},
                                {0, 0, 0, 1}
                            };

    return Linear_Map(matrix);
}

Linear_Map translation(float v[3]) 
{
    float matrix[4][4] =    {   {1,0,0,v[0]},
                                {0,1,0,v[1]},
                                {0,0,1,v[2]},
                                {0,0,0,1}
                            };
    
    return Linear_Map(matrix);
}

Linear_Map Linear_Map::inverse() const
{
    return (*this);
}

Linear_Map Linear_Map::operator*(Linear_Map l) const
{
    float res[4][4];
    matrix_multiplication(this->matrix, l.matrix, res);
    
    return Linear_Map(res);
}

Geometric Linear_Map::operator*(Geometric g) const
{
    float res[N];
    float aux = 0;

    //Multiply the matrix and the vector
    for(int row=0; row<N; row++){
        aux = 0;
        for(int k=0; k<N; k++){
            aux += this->matrix[row][k] * g[k];
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
