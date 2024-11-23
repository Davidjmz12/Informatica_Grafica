#include "kernel_density/cone_density.hpp"

ConeKernel::ConeKernel():
    Kernel()
{}

ConeKernel::~ConeKernel()
{}

double ConeKernel::eval(double distance, double radius) const
{
    if(geqD(distance,radius))
        return 0;
    
    return 3/(M_PI*pow(radius,2)) * (1 - distance/radius);
}
