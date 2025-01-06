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

Base::Base(const Point& p, const Vector& i, const Vector& j, const Vector& k)
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

Base Base::complete_base_k(const Point& c, const Vector& v)
{
    auto candidate = Vector(1,0,0);
    if(candidate.linearly_dependent(v))
        candidate = Vector(0,1,0);
    
    Vector k = v.normalize();
    Vector i = (candidate - k*(candidate.dot(k))).normalize();
    Vector j = k.cross(i);

    return {c, i, j, k};
}

Vector Base::sample_hemisphere(const Vector& normal, const Point& p)
{
    double theta = randomD(0,1);
    double phi = randomD(0,2*M_PI);

    theta = asin(theta);

    Base b = Base::complete_base_k(p, normal);
    Vector base_v = Vector(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
    Vector v = Vector(b.coord_into_canonical(&base_v));

    return v;
}

LinearMap Base::canonical_to_base() const
{
    return {this->_matrix};
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
    return {Point(),
                Vector(1,0,0),
                Vector(0,1,0),
                Vector(0,0,1)};
}

Base Base::normalize() const
{
    return {this->_center,
                this->_i.normalize(),
                this->_j.normalize(),
                this->_k.normalize()};
}

std::ostream& operator<<(std::ostream& os, const Base& b)
{
    os << b.to_string();
    return os;
}

std::string Base::to_string() const
{
    std::string s = "Point: " + this->_center.to_string() + " Base: " + this->_i.to_string() + " ; " + this->_j.
        to_string() + " ; " + this->_k.to_string();
    return s;
}

Vector Base::operator[](const int i) const
{
    if(i < 0 || i > 2)
        throw std::invalid_argument("Index out of bounds.");

    if(i == 0)
        return this->_i;
    if(i == 1) 
        return this->_j;

    return this->_k;
}

bool Base::operator==(const Base& b) const
{
    return (this->_matrix == b._matrix);
}