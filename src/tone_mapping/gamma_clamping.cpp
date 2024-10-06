#include "tone_mapping/gamma_clamping.hpp"

GammaClamping::GammaClamping(double gamma, double V, double LMax)
    : ToneMapping(LMax), _gamma(gamma), _V(V)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
    else if (LMax < V)
        throw std::invalid_argument("Clamping value is greater than 0.");
    
    // Check gamma
    if (gamma <= 0)
        throw std::invalid_argument("Gamma value is less than or equal to 0.");
}

double GammaClamping::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else if (l_in < this->_V)
        return pow(l_in / this->_V, this->_gamma);
    else
        return 1;
}