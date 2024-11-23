#pragma once


#include <stdexcept>
#define _USE_MATH_DEFINES
#include <cmath>

class Kernel 
{
public:
    Kernel();
    virtual ~Kernel();
    virtual double operator()(double distance, double radius) const = 0;
};