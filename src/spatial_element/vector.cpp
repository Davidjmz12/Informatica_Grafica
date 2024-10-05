/**
 * @file vector.cpp
 * @brief Implements vectors.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the implementation of the Vector
 * class, which represents vectors with 3 components.
*/

#include "spatial_element/vector.hpp"

Vector::Vector(double x, double y, double z)
    : SpatialElement(x,y,z)
{}

Vector::Vector()
    : SpatialElement(0,0,0)
{}

double Vector::norm() const
{
    return sqrt(pow((*this)[0],2) +
                pow((*this)[1],2) +
                pow((*this)[2],2));
}

Vector Vector::normalize() const
{
    double norm = this->norm();
    return Vector(  (*this)[0] / norm,
                    (*this)[1] / norm,
                    (*this)[2] / norm
    );
}

double Vector::dot(const Vector* v) const
{
    return  (*this)[0] * v->_coordinates[0] +
            (*this)[1] * v->_coordinates[1] +
            (*this)[2] * v->_coordinates[2];
}

Vector Vector::cross(const Vector* v) const
{
    return Vector(  (*this)[1] * v->_coordinates[2] -
                        (*this)[2] * v->_coordinates[1],
                    (*this)[2] * v->_coordinates[0] -
                        (*this)[0] * v->_coordinates[2],
                    (*this)[0] * v->_coordinates[1] -
                        (*this)[1] * v->_coordinates[0]
    );
}

bool Vector::linearly_dependent(const Vector* v) const
{
    return Vector() == Vector();
}

bool Vector::is_base(const Vector* v1, const Vector* v2) const
{
    double determinant =    (*this)[0]*(*v1)[1]*(*v2)[2] +
                            (*v1)[0]*(*v2)[1]*(*this)[2] + 
                            (*v2)[0]*(*this)[1]*(*v1)[2] -
                            (*this)[2]*(*v1)[1]*(*v2)[0] -
                            (*this)[1]*(*v1)[0]*(*v2)[2] -
                            (*this)[0]*(*v1)[2]*(*v2)[1];

    return !eqFloat(determinant,0); 
}

Vector Vector::operator+(const Vector v) const
{
    return Vector(  (*this)[0] + v[0] , 
                    (*this)[1] + v[1] ,
                    (*this)[2] + v[2]
    );
}

Point Vector::operator+(const Point p) const
{
    return Point(   (*this)[0] + p[0] , 
                    (*this)[1] + p[1] ,
                    (*this)[2] + p[2]
    );
}

Vector Vector::operator-(const Vector v) const
{
    return Vector(  (*this)[0] - v[0] , 
                    (*this)[1] - v[1] ,
                    (*this)[2] - v[2]
    );
}

Vector Vector::operator*(double scalar) const
{
    return Vector(  (*this)[0] * scalar , 
                    (*this)[1] * scalar ,
                    (*this)[2] * scalar
    );
}

Vector Vector::operator/(double scalar) const
{
    if (scalar == 0)
        throw std::runtime_error("Division by zero.");

    return (*this)*(1/scalar);
}

bool Vector::operator==(const Vector v) const
{
    return  eqFloat((*this)[0],v[0]) &&
            eqFloat((*this)[1],v[1]) &&
            eqFloat((*this)[2],v[2]);
}
