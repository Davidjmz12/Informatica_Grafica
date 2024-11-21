#include"color/tone_mapping/gamma.hpp"

Gamma::Gamma(double gamma, double V)
    :_gamma(gamma), _V(V)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
    
    // Check gamma
    if (gamma <= 0)
        throw std::invalid_argument("Gamma value is less than or equal to 0.");
}

double Gamma::evaluate(double l_in) const
{
    if (l_in < this->_V)
        return pow(l_in / this->_V, 1.0/this->_gamma);
    else
        return 1;
}