#include "kernel_density/gauss_density.hpp"

GaussKernel::GaussKernel(double alpha):
    Kernel(), _alpha(alpha)
{
    if (alpha <= 0)
    {
        throw std::invalid_argument("GaussKernel: alpha must be positive");
    }
}

GaussKernel::~GaussKernel()
{}

double GaussKernel::eval(double distance, double radius) const
{
    if (distance > radius)
    {
        return 0;
    }
    double sigma = radius / _alpha;
    return 1.0/sqrt(2*M_PI)/sigma * exp(-pow(distance,2)/(2*pow(sigma,2)));

}