#pragma once

#include "color/tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the clamping technique.
 */
class Clamping : public ToneMapping
{
public:

    /**
     * @brief Construct a new Clamping object.
     */
    Clamping();

    /**
     * @brief Evaluate the clamping tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;

};
