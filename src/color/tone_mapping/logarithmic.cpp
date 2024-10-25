#include"color/tone_mapping/logarithmic.hpp"

Logarithmic::Logarithmic(double V, double alpha)
    : _V(V), _alpha(alpha)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
    // Check alpha
    if (alpha <= 0)
        throw std::invalid_argument("Alpha must be greater than 0.");
}

double Logarithmic::evaluate(double l_in) const
{
    if (l_in < this->_V)
        return log(1+this->_alpha*l_in/this->_V) / log(1+this->_alpha);
    else
        return 1;
}
