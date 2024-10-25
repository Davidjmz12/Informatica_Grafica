#include"color/tone_mapping/drago.hpp"

Drago::Drago(double V):
    _V(V)
{}

double Drago::evaluate(double l_in) const
{
    if(l_in < this->_V)
        return log(1+l_in) / log(1+this->_V);
    else
        return 1;
}

