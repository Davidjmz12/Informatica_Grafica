#include "vector.hpp"
#include <math.h>

Vector::Vector(float x,float y,float z) {
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
}

Vector Vector::operator+(Vector const v) const {
    return Vector(  this->coord[0] + v.coord[0],
                    this->coord[1] + v.coord[1],
                    this->coord[2] + v.coord[2]
    );   
}

Vector Vector::operator-(Vector const v) const {
    return Vector(  this->coord[0] - v.coord[0],
                    this->coord[1] - v.coord[1],
                    this->coord[2] - v.coord[2]
    );
}

Vector Vector::operator*(float scalar) const {
    return Vector(
        this->coord[0]*scalar,
        this->coord[1]*scalar,
        this->coord[2]*scalar
    );
}

Vector Vector::operator/(float scalar) const {
    return Vector(
        this->coord[0]/scalar,
        this->coord[1]/scalar,
        this->coord[2]/scalar
    );
}

bool Vector::operator==(Vector const v) const {
    return  this->coord[0] == v.coord[0] &&
            this->coord[1] == v.coord[1] &&
            this->coord[2] == v.coord[2];
}

float Vector::norm() const {
    return sqrt(pow(this->coord[0],2)+pow(this->coord[1],2)+pow(this->coord[2],2));
}

Vector Vector::normalize() const {
    return Vector(this->coord[0],
            this->coord[1],
            this->coord[2]) * this->norm();
}

float Vector::dot(Vector const v) const {
    return  (this->coord[0]*v.coord[0] + 
            this->coord[1]*v.coord[1] +
            this->coord[2]*v.coord[2]);   
}

Vector Vector::cross(Vector const v) const {
    return Vector(
        this->coord[1] * v.coord[2] - this->coord[2] * v.coord[1],
        this->coord[2] * v.coord[0] - this->coord[0] * v.coord[2],
        this->coord[0] * v.coord[1] - this->coord[1] * v.coord[0]
    );

}

std::ostream& operator<<(std::ostream& os, const Vector& v){
    std::cout << "(" << v.coord[0] << "," <<
                        v.coord[1] << "," <<
                        v.coord[2] << ")";
    return os;
}