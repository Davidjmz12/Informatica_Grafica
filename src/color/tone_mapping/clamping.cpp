#include"color/tone_mapping/clamping.hpp"

Clamping::Clamping()
{}

double Clamping::evaluate(double l_in) const
{
    if (l_in < 1)
        return l_in;
    else
        return 1;
}