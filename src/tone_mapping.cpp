#include "tone_mapping.hpp"

ToneMapping::ToneMapping(double LMax)
    : _LMax(LMax)
{
    // Check LMax
    if (LMax <= 0)
        throw std::invalid_argument("LMax cannot is less or equal to 0.");
}

double ToneMapping::max_luminance() const
{
    return this->_LMax;
}

// -----------------------------------------------------
//                      CLAMPING
// -----------------------------------------------------

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


// -----------------------------------------------------
//                      EQUALIZATION
// -----------------------------------------------------

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


// -----------------------------------------------------
//              EQUALIZATION CLAMPING
// -----------------------------------------------------

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


// -----------------------------------------------------
//                      GAMMA
// -----------------------------------------------------

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


// -----------------------------------------------------
//                  GAMMA CLAMPING
// -----------------------------------------------------

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


// -----------------------------------------------------
//                        DRAGO
// -----------------------------------------------------

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


// -----------------------------------------------------
//                      LOGARITHMIC
// -----------------------------------------------------


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
