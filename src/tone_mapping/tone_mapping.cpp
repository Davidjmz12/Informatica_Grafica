#include <stdexcept>

#include "tone_mapping/tone_mapping.hpp"

ToneMapping::ToneMapping(double LMax)
    : _LMax(LMax)
{
    // Check LMax
    if (LMax <= 0)
        throw std::invalid_argument("LMax cannot is less or equal to 0.");
}

double ToneMapping::max_luminance() const
{
    return this->_LMax;
}