#include "tone_mapping/gamma.hpp"

Gamma::Gamma(double gamma, double LMax)
    : ToneMapping(LMax), _gamma(gamma)
{
    // Check gamma
    if (gamma <= 0)
        throw std::invalid_argument("Gamma value is less than or equal to 0.");
}

double Gamma::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return pow(l_in / this->_LMax, this->_gamma);
}
