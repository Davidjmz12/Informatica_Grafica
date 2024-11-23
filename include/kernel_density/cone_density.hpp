#pragma once

#include "kernel_density/kernel_density.hpp"

class ConeKernel : public Kernel
{
public:
    ConeKernel();
    virtual ~ConeKernel();
    virtual double operator()(double distance, double radius) const;
};
