#include "tone_mapping.hpp"

ToneMapping::ToneMapping(float LMax)
    : _LMax(LMax)
{
    // Check LMax
    if (LMax <= 0)
        throw std::invalid_argument("LMax cannot is less or equal to 0.");
}

float ToneMapping::max_luminance() const
{
    return this->_LMax;
}

// -----------------------------------------------------
//                      CLAMPING
// -----------------------------------------------------

Clamping::Clamping(float LMax)
    :ToneMapping(LMax)
{}

float Clamping::evaluate(float l_in) const
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

Equalization::Equalization(float LMax)
    :ToneMapping(LMax)
{}

float Equalization::evaluate(float l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return l_in / this->_LMax;
}


// -----------------------------------------------------
//              EQUALIZATION CLAMPING
// -----------------------------------------------------

EqualizationClamping::EqualizationClamping(float V, float LMax)
    :ToneMapping(LMax), _V(V)
{
    // Check V
    if (V <= 0)
        throw std::invalid_argument("Clamping value is less or equal to 0.");
    else if (LMax < V)
        throw std::invalid_argument("Clamping value is greater than 0.");
}

float EqualizationClamping::evaluate(float l_in) const
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

Gamma::Gamma(float gamma, float LMax)
    : ToneMapping(LMax), _gamma(gamma)
{
    // Check gamma
    if (gamma <= 0)
        throw std::invalid_argument("Gamma value is less than or equal to 0.");
}

float Gamma::evaluate(float l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else
        return pow(l_in / this->_LMax, this->_gamma);
}


// -----------------------------------------------------
//                  GAMMA CLAMPING
// -----------------------------------------------------

GammaClamping::GammaClamping(float gamma, float V, float LMax)
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

float GammaClamping::evaluate(float l_in) const
{
    if (l_in < 0 || l_in > this->_LMax)
        throw std::invalid_argument("Luminance value is strange.");
    else if (l_in < this->_V)
        return pow(l_in / this->_V, this->_gamma);
    else
        return 1;
}