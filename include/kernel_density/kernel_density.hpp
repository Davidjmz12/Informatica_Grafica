#pragma once


#include <stdexcept>
#include <cmath>

class Kernel 
{
public:
    Kernel() = default;
    virtual double eval(double distance, double radius) const = 0;
};