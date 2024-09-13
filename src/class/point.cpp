#include "point.hpp"

Point::Point(float x, float y, float z){
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
}


Point Point::operator+(Vector const v) const {
    return Point(   this->coord[0] + v.coord[0],
                    this->coord[1] + v.coord[1],
                    this->coord[2] + v.coord[2]
    );
}


Vector Point::operator-(Point const p) const {
    return Vector(  this->coord[0] - p.coord[0],
                    this->coord[1] - p.coord[1],
                    this->coord[2] - p.coord[2]
    );
}

Point Point::operator*(float scalar) const {
    return Point(  this->coord[0] * scalar,
                    this->coord[1] * scalar,
                    this->coord[2] * scalar
    );
}

Point Point::operator/(float scalar) const {
    return Point(  this->coord[0] / scalar,
                    this->coord[1] / scalar,
                    this->coord[2] / scalar
    );
}

std::ostream& operator<<(std::ostream& os,const Point& p){
    std::cout << "(" << p.coord[0] << "," <<
                        p.coord[1] << "," <<
                        p.coord[2] << ")";
    return os;
}


bool Point::operator==(Point const p) const {
    return  (this->coord[0] == p.coord[0] &&
             this->coord[1] == p.coord[1] &&
             this->coord[2] == p.coord[2]
    );
}

