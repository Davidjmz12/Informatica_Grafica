#include "tone_mapping/drago.hpp"

Drago::Drago(double LMax)
    : ToneMapping(LMax)
{}

double Drago::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return log(1+l_in) / log(1+this->_LMax);
}

