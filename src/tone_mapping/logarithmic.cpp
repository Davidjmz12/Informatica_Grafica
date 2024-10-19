#include "tone_mapping/logarithmic.hpp"

Logarithmic::Logarithmic(double LMax, double alpha)
    : ToneMapping(LMax), _alpha(alpha)
{
    // Check alpha
    if (alpha <= 0)
        throw std::invalid_argument("Alpha must be greater than 0.");
}

double Logarithmic::evaluate(double l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return log(1+this->_alpha*l_in/this->_LMax) / log(1+this->_alpha);
}
