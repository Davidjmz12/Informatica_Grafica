#include "kernel_density/cone_density.hpp"

ConeKernel::ConeKernel():
    Kernel()
{}

ConeKernel::~ConeKernel()
{}

double ConeKernel::eval(double distance, double radius) const
{
    return 3/(M_PI*radius*radius) * (1 - distance/radius);
}
