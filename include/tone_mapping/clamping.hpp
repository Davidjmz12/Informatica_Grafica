#pragma once

#include "tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the clamping technique.
 */
class Clamping : public ToneMapping
{
public:

    /**
     * @brief Construct a new Clamping object.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    Clamping(double LMax);

    /**
     * @brief Evaluate the clamping tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;

};
