#include "tone_mapping.hpp"

ToneMapping::ToneMapping(float gamma, float slope, float V, float LMax)
    : _gamma(gamma), _slope(slope), _V(V), _LMax(LMax) {}
