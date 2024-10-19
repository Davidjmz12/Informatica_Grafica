/**
 * @file point.cpp
 * @brief Defines points.
 * @author David Tizne, David Jimenez
 * @date 5/10/2024
 *
 * This file contains the implementation of the Point
 * class, which represents points with 3 components.
*/

#include "spatial_element/point.hpp"

Point::Point(double x, double y, double z)
    : SpatialElement(x,y,z,1)
{}

Point::Point(SpatialElement* s)
    : SpatialElement(*s)
{}

Point::Point(const Vector v)
    : SpatialElement(v[0],v[1],v[2],1)
{}

Point::Point()
    : SpatialElement(0,0,0,1)
{}

bool Point::is_point() const
{
    return true;
}

Point Point::operator+(const Vector v) const
{
    return Point(   (*this)[0] + v[0] , 
                    (*this)[1] + v[1] ,
                    (*this)[2] + v[2]
    );
}

Point Point::operator-(const Vector v) const
{
    return Point(   (*this)[0] - v[0] , 
                    (*this)[1] - v[1] ,
                    (*this)[2] - v[2]
    );
}

Vector Point::operator-(const Point p) const
{
    return Vector(  (*this)[0] - p[0] , 
                    (*this)[1] - p[1] ,
                    (*this)[2] - p[2]
    );
}

bool Point::operator==(const Point v) const
{
    return  eqD((*this)[0],v[0]) &&
            eqD((*this)[1],v[1]) &&
            eqD((*this)[2],v[2]);
}

std::string Point::to_string() const
{
    return "Point: (" + std::to_string((*this)[0]) + "," + std::to_string((*this)[1]) + "," + std::to_string((*this)[2]) + ")";
}
