#include "point.hpp"
#include <iostream>

int main(){

    Point a = Point(1,2,3);
    Point b = Point(1,2,3);

    std::cout << "Point A: " << a <<
       "\n" << "Point B: " << b << std::endl;

    Vector v = Vector(4,5,6);
    std::cout << "Vector V: " << v << std::endl;

    Vector e1 = Vector(1,2,0);
    Vector e2 = Vector(1,1,3);

    std::cout << "e1 x e2 = " << e1 << " x " << e2 << " = " << e1.cross(e2) << std::endl;
    return 0;
}