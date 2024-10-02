/**
 * @file base.cpp
 * @brief Implementation of base header.
 * @authors Davidjmz12 DavidTizne
 * @date 18/09/2024
 * @see base.hpp for more information.
 * This file contains the implementation of the Base class, which represents
 * a 3D base.
*/

#include "base.hpp"

Base::Base(Geometric p, Geometric i, Geometric j, Geometric k)
    : center(p), x(i), y(j), z(k)
{ 
    if (p.is_vector() || i.is_point() || j.is_point() || k.is_point())
        throw std::invalid_argument("p must be a point and i,j,k must be vectors.");

    if (!i.is_base(j,k))
        throw std::invalid_argument("Vectors must be linearly independent.");
    
    float aux[4][4] = { {i[0], j[0], k[0], p[0]},
                        {i[1], j[1], k[1], p[1]},
                        {i[2], j[2], k[2], p[2]},
                        {0   , 0   , 0   , 1   }};

    this->matrix = Matrix4x4(aux);
    this->matrix_inverse = Matrix4x4(aux).inverse();
}


LinearMap Base::canonical_to_base() const
{
    return LinearMap(this->matrix);
}

Geometric Base::coord_from_canonical(Geometric g) const
{
    if(!g.is_vector())
        throw std::invalid_argument("Geometric must be a vector.");
    return LinearMap(this->matrix_inverse)*g;
}
        
Geometric Base::coord_into_canonical(Geometric g) const
{
    return this->x*g[0] + this->y*g[1] + this->z*g[2];
}

Base Base::canonic_base(){
    return Base(Geometric::point(0,0,0), 
                Geometric::vector(1,0,0),
                Geometric::vector(0,1,0),
                Geometric::vector(0,0,1));
}

std::ostream& operator<<(std::ostream& os, const Base& b)
{
    os << "Point: " << b.center << "\nBase: " << b.x << " ; " << b.y << " ; " << b.z; 
    return os;
}

bool Base::operator==(Base b) const
{
    return (this->matrix == b.matrix);
}