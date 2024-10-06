#pragma once

#include "tone_mapping/tone_mapping.hpp"

class Drago : public ToneMapping
{
public:
    Drago(double LMax);

    double evaluate(double l_in) const;
};


