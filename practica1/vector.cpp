#include "vector.hpp"
#include <math.h>

Vector Vector::operator+(Vector const v){
    return Vector(  this->coord[0] + v.coord[0],
                    this->coord[1] + v.coord[1],
                    this->coord[2] + v.coord[2]
    )   
}
Vector Vector::operator-(Vector const v) {
    return Vector(  this->coord[0] - v.coord[0],
                    this->coord[1] - v.coord[1],
                    this->coord[2] - v.coord[2]
    )
}

Vector Vector::operator*(float scalar) {
    return Vector(
        this->coord[0]*scalar,
        this->coord[1]*scalar,
        this->coord[2]*scalar
    );
}

Vector Vector::operator/(float scalar) {

    return Vector(
        this->coord[0]/scalar,
        this->coord[1]/scalar,
        this->coord[2]/scalar
    );
}

float Vector::norm() const {
    return sqrt(pow(this->coord[0],2)+pow(this->coord[1],2)+pow(this->coord[2],2));
}

Vector Vector::normalize() const {
    return *this / this->norm();
}

float Vector::dot(Vector const v1, Vector const v2){
    
}
Vector Vector::cross(Vector const v1, Vector const v2){
}

std::ostream& operator<<(std::ostream& os, const Vector& v){
    return os;
}