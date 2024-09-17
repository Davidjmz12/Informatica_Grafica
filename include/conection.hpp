/**
 * @file conection.hpp
 * @brief Defines a conection class.
 *       It conteins 
 *
 * This file contains the definition of the Base class, which represents
 * a base in R^3.
*/
#ifndef CONECTION_HPP
#define CONECTION_HPP

#include <iostream>

#include "sphere.hpp"

class Connection
{
    private:
        Base b1, b2;
        bool collide_;
        Geometric coord_b1, coord_b2;
        
    public:
        Connection(Sphere s1, float az1, float inc1, Sphere s2, float az2, float inc2);
        
        bool collide() const;
        Geometric coord_in_base_1() const;
        Geometric coord_in_base_2() const;
        
};

#endif
