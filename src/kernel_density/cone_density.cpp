#include "kernel_density/cone_density.hpp"

#include "global_config/constants.hpp"

ConeKernel::ConeKernel():
    Kernel()
{}

ConeKernel::~ConeKernel()
{}

double ConeKernel::eval(double distance, double radius) const
{
    if(geD(distance,radius))
        return 0;
    
    return 3.0/(M_PI*pow(radius,2)) * (1 - distance/radius);
}
