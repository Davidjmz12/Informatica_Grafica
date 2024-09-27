#include "tone_mapping.hpp"


ToneMapping::ToneMapping(float gamma, float V, float LMax)
    : _gamma(gamma), _V(V), _LMax(LMax) {}


ToneMapping ToneMapping::clamping(float LMax)
{
    return ToneMapping(1,1,LMax);
}

ToneMapping ToneMapping::equalization(float LMax)
{
    return ToneMapping(1,LMax,LMax);
}

ToneMapping ToneMapping::equalization_clamping(float V, float LMax)
{
    return ToneMapping(1,V,LMax);
}

ToneMapping ToneMapping::gamma(float gamma, float LMax)
{
    return ToneMapping(gamma,LMax,LMax);
}

ToneMapping ToneMapping::gamma_clamping(float gamma, float V, float LMax)
{
    return ToneMapping(gamma,V,LMax);
}

float ToneMapping::evaluate(float l_in)
{
    if(l_in < this->_V)
    {
        return pow(l_in/this->_LMax,this->_gamma);
    } else if (this->_V <= l_in <= this->_LMax){
        return 1;
    } else {
        throw std::invalid_argument("Luminance value is greater than LMax");
    }
}