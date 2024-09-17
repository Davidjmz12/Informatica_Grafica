#include "conection.hpp"


Conection::Conection(Sphere s1, float az1, float inc1, Sphere s2, float az2, float inc2)
    : b1(s1.base_point(az1,inc1)), 
      b2(s2.base_point(az2,inc2)), 
      coord_b1(b1.coord_from_canonical(b2.center)),
      coord_b2(b1.coord_from_canonical(b1.center)),
      collide_(coord_b1[2] < 0 || coord_b2[2] < 0) 
{}

bool Conection::collide() const
{
    return this->collide_;
}

Geometric Conection::coord_in_base_1() const
{
    return this->coord_b1;
}

Geometric Conection::coord_in_base_2() const
{
    return this->coord_b2;
}