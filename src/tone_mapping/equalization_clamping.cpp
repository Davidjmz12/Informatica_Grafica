#include "tone_mapping/equalization_clamping.hpp"

EqualizationClamping::EqualizationClamping(double V, double LMax)
    :ToneMapping(LMax), _V(V)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
    else if (LMax < V)
        throw std::invalid_argument("Clamping value is greater than 0.");
}

double EqualizationClamping::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else if (l_in < this->_V)
        return l_in / this->_V;
    else
        return 1;
}