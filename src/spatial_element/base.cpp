/**
 * @file base.cpp
 * @brief Implementation of base header.
 * @authors Davidjmz12 DavidTizne
 * @date 18/09/2024
 * @see base.hpp for more information.
 * This file contains the implementation of the Base class, which represents
 * a 3D base.
*/

#include "spatial_element/base.hpp"

Base::Base(Point p, Vector i, Vector j, Vector k)
    : _center(p), _i(i), _j(j), _k(k)
{ 
    if (!i.is_base(j, k))
        throw std::invalid_argument("Vectors must be linearly independent.");
    
    double aux[4][4] = { {i[0], j[0], k[0], p[0]},
                        {i[1], j[1], k[1], p[1]},
                        {i[2], j[2], k[2], p[2]},
                        {0   , 0   , 0   , 1   }};

    this->_matrix = Matrix4x4(aux);
}

Base Base::complete_base_k(Point c, Vector v)
{
    Vector candidate = Vector(1,0,0);
    if(candidate.linearly_dependent(v))
        candidate = Vector(0,1,0);
    
    Vector k = v.normalize();
    Vector i = (candidate - k*(candidate.dot(k))).normalize();
    Vector j = k.cross(i);

    return Base(c, i, j, k);
}

LinearMap Base::canonical_to_base() const
{
    return LinearMap(this->_matrix);
}

SpatialElement* Base::coord_from_canonical(const SpatialElement* s) const
{
    return LinearMap(this->_matrix.inverse())*s;
}
        
SpatialElement* Base::coord_into_canonical(const SpatialElement* s) const 
{
    return LinearMap(this->_matrix)*s;
}

Point Base::get_center() const
{
    return this->_center;
}

Base Base::canonic_base()
{
    return Base(Point(),
                Vector(1,0,0),
                Vector(0,1,0),
                Vector(0,0,1));
}

Base Base::normalize() const
{
    return Base(this->_center,
                this->_i.normalize(),
                this->_j.normalize(),
                this->_k.normalize());
}

std::ostream& operator<<(std::ostream& os, const Base& b)
{
    os << "Point: " << b._center << "\nBase: " << b._i << " ; " << b._j << " ; " << b._k; 
    return os;
}

Vector Base::operator[](int i) const
{
    if(i < 0 || i > 2)
        throw std::invalid_argument("Index out of bounds.");
    if(i == 0)
        return this->_i;
    if(i == 1) 
        return this->_j;
    else
        return this->_k;
}

bool Base::operator==(Base b) const
{
    return (this->_matrix == b._matrix);
}