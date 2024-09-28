#include "tone_mapping.hpp"

ToneMapping::ToneMapping(float gamma, float V, float LMax)
{
    if(V>LMax)
    {
        throw std::invalid_argument("Clamping value is greater than LMax");
    }
    if(LMax<=0)
    {
        throw std::invalid_argument("LMax value is less than or equal to 0");
    }
    if(gamma<=0)
    {
        throw std::invalid_argument("Gamma value is less than or equal to 0");
    }

    this->_gamma = gamma;
    this->_V = V;
    this->_LMax = LMax;

}

float ToneMapping::getMax() const
{
    return this->_LMax;
}

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

float ToneMapping::evaluate(float l_in) const
{   
    if(l_in < 0)
    {
        throw std::invalid_argument("Luminance value is less than 0");
    } else if(l_in < this->_V)
    {
        return pow(l_in/this->_V,this->_gamma);
    } else if (this->_V <= l_in && l_in <= this->_LMax)
    {
        return 1;
    } else 
    {
        throw std::invalid_argument("Luminance value is greater than LMax");
    }
}


std::ostream& operator<<(std::ostream& os,const ToneMapping& g)
{
    os << "ToneMapping: gamma factor " << g._gamma << " clamping at " << g._V << " with max " << g._LMax;
    return os;
}
