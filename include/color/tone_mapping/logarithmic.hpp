#pragma once

#include "color/tone_mapping/tone_mapping.hpp"

class Logarithmic : public ToneMapping
{
private:
    double _alpha;
    double _V;
    
public:
    Logarithmic(double V, double alpha);

    double evaluate(double l_in) const;
};
