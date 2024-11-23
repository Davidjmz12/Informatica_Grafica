#include "kernel_density/gauss_density.hpp"

GaussKernel::GaussKernel(double alpha):
    Kernel(), _alpha(alpha)
{
    if (alpha <= 1)
    {
        throw std::invalid_argument("GaussKernel: alpha must be positive");
    }
}

GaussKernel::~GaussKernel()
{}

double GaussKernel::operator()(double distance, double radius) const
{
    return _alpha/(M_PI*pow(radius, 2)*(1-exp(-_alpha))) * exp(-_alpha*pow(distance/radius,2));
}