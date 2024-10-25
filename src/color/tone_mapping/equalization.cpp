#include "color/tone_mapping/equalization.hpp"

Equalization::Equalization(double V)
    :_V(V)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
}

double Equalization::evaluate(double l_in) const
{
    if (l_in < this->_V)
        return l_in / this->_V;
    else
        return 1;
}