#include "linear_map.hpp"
#include "matrix.hpp"

Linear_Map::Linear_Map(Matrix4x4 M): matrix(M) {}

Linear_Map::Linear_Map(float M[4][4])
    : matrix(Matrix4x4(M)) {}

Linear_Map Linear_Map::change_basis(Base origin, Base b2) 
{
    return b2.canonical_to_base().inverse() * origin.canonical_to_base();
}

Linear_Map Linear_Map::rotation(Geometric axis, float angle) 
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

Linear_Map Linear_Map::scale(float lambda[3]) 
{
    float matrix[4][4] =    {   {lambda[0], 0, 0, 0},
                                {0, lambda[1], 0, 0},
                                {0, 0, lambda[2], 0},
                                {0, 0, 0, 1}
                            };

    return Linear_Map(matrix);
}

Linear_Map Linear_Map::translation(Geometric v) 
{
    if (!v.is_vector())
        throw std::invalid_argument("v must be a vector.");
        
    float matrix[4][4] =    {   {1,0,0,v[0]},
                                {0,1,0,v[1]},
                                {0,0,1,v[2]},
                                {0,0,0,1}
                            };
    
    return Linear_Map(matrix);
}

Linear_Map Linear_Map::identity()
{
    return Linear_Map(Matrix4x4::identity());
}

Linear_Map Linear_Map::inverse() const
{
    return Linear_Map(this->matrix.inverse());
}

Linear_Map Linear_Map::operator*(Linear_Map l) const
{
    return Linear_Map(this->matrix*l.matrix);
}

Geometric Linear_Map::operator*(Geometric g) const
{
    return this->matrix*g ;
}

bool Linear_Map::operator==(Linear_Map l) const
{
    return this->matrix == l.matrix;
}

std::ostream& operator<<(std::ostream& os,const Linear_Map& g)
{
    os << g.matrix;

    return os;
}
