#pragma once

#include <stdexcept>
#include <math.h>

/**
 * @class ToneMapping
 * @brief A class to represent and apply various tone mapping techniques.
 */
class ToneMapping
{
public:
    /**
     * @brief Construct a new ToneMapping object.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    ToneMapping() {}

    /**
     * @brief Evaluate the tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    virtual double evaluate(double l_in) const = 0;

};
