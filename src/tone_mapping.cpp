#include "tone_mapping.hpp"

Tone_mapping::Tone_mapping(float gamma, float slope, float V, float LMax)
    : _gamma(gamma), _slope(slope), _V(V), _LMax(LMax) {}
