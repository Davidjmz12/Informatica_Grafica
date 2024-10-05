/**
 * @file geometric.cpp
 * @brief Implementation of the geometric header.
 * @authors DavidJimenez DavidTizne
 * @date 18/09/2024
 * @see linear_map.hpp for more information.
 * This file contains the implementation of the Linear Map class, which represents
 * a linear application from R^4 to R^4.
*/

#include <math.h>

#include "linear_map.hpp"

LinearMap::LinearMap(Matrix4x4 M): matrix(M) {}

LinearMap::LinearMap(double M[4][4])
    : matrix(Matrix4x4(M)) {}

LinearMap LinearMap::change_basis(Base origin, Base b2) 
{
    return b2.canonical_to_base().inverse() * origin.canonical_to_base();
}

LinearMap LinearMap::rotation(Geometric axis, double angle) 
{
    axis = axis.normalize();

    double Kf[4][4] = {  {0       , -axis[2],   axis[1], 0},
                        {axis[2] ,        0,  -axis[0], 0},
                        {-axis[1],  axis[0],         0, 0},
                        {0       ,        0,         0, 1}
                    };

    Matrix4x4 K = Matrix4x4(Kf);



    Matrix4x4 result = Matrix4x4::identity()+K*sin(angle)+K*K*(1-cos(angle));

    return LinearMap(result);
}

LinearMap LinearMap::scale(double lambda[3]) 
{
    double matrix[4][4] =    {   {lambda[0], 0, 0, 0},
                                {0, lambda[1], 0, 0},
                                {0, 0, lambda[2], 0},
                                {0, 0, 0, 1}
                            };

    return LinearMap(matrix);
}

LinearMap LinearMap::translation(Geometric v) 
{
    if (!v.is_vector())
        throw std::invalid_argument("v must be a vector.");
        
    double matrix[4][4] =    {   {1,0,0,v[0]},
                                {0,1,0,v[1]},
                                {0,0,1,v[2]},
                                {0,0,0,1}
                            };
    
    return LinearMap(matrix);
}

LinearMap LinearMap::identity()
{
    return LinearMap(Matrix4x4::identity());
}

LinearMap LinearMap::inverse() const
{
    return LinearMap(this->matrix.inverse());
}

LinearMap LinearMap::operator*(LinearMap l) const
{
    return LinearMap(this->matrix*l.matrix);
}

Geometric LinearMap::operator*(Geometric g) const
{
    return this->matrix*g ;
}

bool LinearMap::operator==(LinearMap l) const
{
    return this->matrix == l.matrix;
}

std::ostream& operator<<(std::ostream& os,const LinearMap& g)
{
    os << g.matrix;

    return os;
}
