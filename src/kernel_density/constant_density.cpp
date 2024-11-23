#include "kernel_density/constant_density.hpp"

ConstantKernel::ConstantKernel()
{}

ConstantKernel::~ConstantKernel()
{}

double ConstantKernel::operator()(double distance, double radius) const
{
    return 1/(M_PI*radius*radius);
}