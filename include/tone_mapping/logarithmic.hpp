#pragma once

#include "tone_mapping/tone_mapping.hpp"

class Logarithmic : public ToneMapping
{
private:
    double _alpha;
    
public:
    Logarithmic(double LMax, double alpha);

    double evaluate(double l_in) const;
};
