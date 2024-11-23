#pragma once

#include "kernel_density/kernel_density.hpp"

class ConstantKernel : public Kernel
{
public:
    ConstantKernel();
    virtual ~ConstantKernel();
    virtual double operator()(double distance, double radius) const;
};
