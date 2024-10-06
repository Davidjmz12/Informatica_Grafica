#include "tone_mapping/equalization.hpp"

Equalization::Equalization(double LMax)
    :ToneMapping(LMax)
{}

double Equalization::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return l_in / this->_LMax;
}
