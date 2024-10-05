/**
 * @file geometric.cpp
 * @brief Implementation of the geometric header.
 * @authors DavidJimenez DavidTizne
 * @date 18/09/2024
 * @see geometric.hpp for more information.
 * This file contains the implementation of the Geometric class, which represents
 * a point or a vector.
*/

#include <math.h>
#include <iostream>
#include <iomanip>

#include "geometric.hpp"

Geometric::Geometric()
{
    v = {0,0,0,0};
}

Geometric::Geometric(double a0, double a1, double a2, double a3)
{   
    if (a3 != 0)
        v = {a0/a3,a1/a3,a2/a3,1};
    else 
        v = {a0,a1,a2,0};
    
}

Geometric Geometric::point(double x, double y, double z) 
{
    return Geometric(x,y,z,1);
}

Geometric Geometric::point0()
{
    return Geometric(0,0,0,1);
}

Geometric Geometric::vector0()
{
    return Geometric(0,0,0,0);
}

Geometric Geometric::vector(double x, double y, double z)
{
    return Geometric(x,y,z,0);
}

bool Geometric::is_point() const 
{
    return this->v[3] == 1;
}

bool Geometric::is_vector() const
{
    return this->v[3] == 0;
}

double Geometric::norm() const 
{
    if (!this->is_vector())
        throw std::invalid_argument("The geometric must be a vector, not a point.");
    
    return sqrt(pow(this->v[0],2) + pow(this->v[1],2) + pow(this->v[2],2));
}

Geometric Geometric::normalize() const
{
    if (!this->is_vector())
        throw std::invalid_argument("The geometric must be a vector, not a point.");
    
    double norm = this->norm();
    return Geometric(   this->v[0] / norm,
                        this->v[1] / norm,
                        this->v[2] / norm,
                        this->v[3]
    );
}

double Geometric::dot(Geometric const g) const
{
    if (!(this->is_vector() && g.is_vector()))
        throw std::invalid_argument("Both geometric must be vectors.");
    
    return  (this->v[0] * g.v[0] +
             this->v[1] * g.v[1] +
             this->v[2] * g.v[2] 
    );

}

Geometric Geometric::cross(Geometric const g) const
{
    if (!(this->is_vector() && g.is_vector()))
        throw std::invalid_argument("Both geometric must be vectors.");
    
    return Geometric::vector(
                        this->v[1] * g.v[2] - this->v[2] * g.v[1],
                        this->v[2] * g.v[0] - this->v[0] * g.v[2],
                        this->v[0] * g.v[1] - this->v[1] * g.v[0]
    );
}

bool Geometric::linearly_dependent(Geometric const g) const
{
    if (!(this->is_vector() && g.is_vector()))
        throw std::invalid_argument("Both geometric must be vectors.");

    return this->cross(g) == Geometric::vector(0,0,0);
}

bool Geometric::is_base(Geometric g1, Geometric g2) const
{
    if (!(this->is_vector() && g1.is_vector() && g2.is_vector()))
        throw std::invalid_argument("All three geometric must be vectors.");
    

    double determinant =   ((*this)[0]*g1[1]*g2[2] + g1[0]*g2[1]*(*this)[2] + g2[0]*(*this)[1]*g1[2] -
                         (*this)[2]*g1[1]*g2[0] - (*this)[1]*g1[0]*g2[2] - (*this)[0]*g1[2]*g2[1]);

    return determinant != 0;  
}

Geometric Geometric::operator+(Geometric const g) const
{
    if (this->is_point() && g.is_point())
        throw std::invalid_argument("Cannot sum two points.");

    return Geometric(this->v[0] + g.v[0] , 
                     this->v[1] + g.v[1] ,
                     this->v[2] + g.v[2] ,
                     this->v[3] + g.v[3]
                     );
}

Geometric Geometric::operator-(Geometric const g) const 
{
    if (this->is_vector() && g.is_point())
        throw std::invalid_argument("Cannot compute vector minus point.");
    
    return Geometric(this->v[0] - g.v[0] , 
                     this->v[1] - g.v[1] ,
                     this->v[2] - g.v[2] ,
                     this->v[3] - g.v[3]
                     );
}
Geometric Geometric::operator*(double scalar) const 
{
    if (!this->is_vector())
        throw std::invalid_argument("Only vectors can be multiply by scalar.");
    return Geometric(this->v[0] * scalar , 
                     this->v[1] * scalar ,
                     this->v[2] * scalar ,
                     this->v[3]
                     );
}

Geometric Geometric::operator/(double scalar) const 
{
    if (!this->is_vector())
        throw std::invalid_argument("Only vectors can be divide by scalar.");

    if (scalar == 0)
        throw std::runtime_error("Division by zero.");
        
    return Geometric(this->v[0] / scalar , 
                     this->v[1] / scalar ,
                     this->v[2] / scalar ,
                     this->v[3]
                     );
}

bool Geometric::operator==(Geometric const g) const 
{
    return  eqD(this->v[0],g.v[0]) &&
            eqD(this->v[1],g.v[1]) &&
            eqD(this->v[2],g.v[2]) &&
            eqD(this->v[3],g.v[3]);
}

std::ostream&  operator<<(std::ostream& os,const Geometric& g) 
{
    std::string type = g.v[3]==1 ? "point":"vector";
    
    os  << type << ": ("  << 
                            std::setprecision(6) << g.v[0] << "," <<
                            std::setprecision(6) << g.v[1] << "," <<
                            std::setprecision(6) << g.v[2] << ")";
    return os;
}

double Geometric::operator[](int index) const{
    if (index < 0 || index > 3)
        throw std::out_of_range("Index must be between 0-3");

    return this->v[index];
}