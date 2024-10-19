#include "tone_mapping/clamping.hpp"

Clamping::Clamping(double LMax)
    :ToneMapping(LMax)
{}

double Clamping::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else if (l_in < 1)
        return l_in;
    else
        return 1;
}