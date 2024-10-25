#pragma once

#include "color/tone_mapping/tone_mapping.hpp"

class Drago : public ToneMapping
{
private:
    double _V;
public:
    Drago(double V);

    double evaluate(double l_in) const;
};


