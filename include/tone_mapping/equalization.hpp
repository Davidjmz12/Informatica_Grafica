#pragma once

#include "tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the equalization technique.
 */
class Equalization : public ToneMapping
{
public:
    /**
     * @brief Construct a new Equalization object.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    Equalization(double LMax);

    /**
     * @brief Evaluate the equalization tone mapping for a given
     * luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;
};
