#pragma once

#include <stdexcept>
#include <math.h>

/**
 * @class ToneMapping
 * @brief A class to represent and apply various tone mapping techniques.
 */
class ToneMapping
{
protected:
    double _LMax; ///< Maximum luminance value for tone mapping

public:
    /**
     * @brief Construct a new ToneMapping object.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    ToneMapping(double LMax);

    /**
     * @brief Evaluate the tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    virtual double evaluate(double l_in) const = 0;

    /**
     * @brief Retrieves the maximum luminance value.
     * 
     * This function returns the highest luminance value that can be achieved.
     * It is useful for tone mapping and other graphics operations where the
     * maximum brightness level needs to be known.
     * 
     * @return The maximum luminance value.
     */
    double max_luminance() const;

};
