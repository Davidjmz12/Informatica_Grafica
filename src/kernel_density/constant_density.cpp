#include "kernel_density/constant_density.hpp"

ConstantKernel::ConstantKernel()
{}

ConstantKernel::~ConstantKernel()
{}

double ConstantKernel::eval(double distance, double radius) const
{
    return 1/(M_PI*radius*radius);
}