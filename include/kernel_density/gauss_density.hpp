#pragma once

#include "kernel_density/kernel_density.hpp"

class GaussKernel : public Kernel
{
private:
    double _alpha;
public:
    GaussKernel(double alpha);
    virtual ~GaussKernel();
    virtual double operator()(double distance, double radius) const;
};
