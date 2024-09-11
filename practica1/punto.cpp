#include "punto.hpp"

Punto::Punto(float x, float y, float z){
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
}


Punto Punto::operator+(Vector const v) const {
    return Punto(   this->coord[0] + v.coord[0],
                    this->coord[1] + v.coord[1],
                    this->coord[2] + v.coord[2]
    );
}


Vector Punto::operator-(Punto const p) const {
    return Vector(  this->coord[0] - p.coord[0],
                    this->coord[1] - p.coord[1],
                    this->coord[2] - p.coord[2]
    );
}

Punto Punto::operator*(float scalar) const {
    return Punto(  this->coord[0] * scalar,
                    this->coord[1] * scalar,
                    this->coord[2] * scalar
    );
}

Punto Punto::operator/(float scalar) const {
    return Punto(  this->coord[0] / scalar,
                    this->coord[1] / scalar,
                    this->coord[2] / scalar
    );
}

std::ostream& operator<<(std::ostream& os,const Punto& p){
    std::cout << "(" << p.coord[0] <<
                        p.coord[1] <<
                        p.coord[2] << ")";
    return os;
}
