#pragma once

#include "tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the gamma technique.
 */
class Gamma : public ToneMapping
{
private:
    double _gamma;   ///< Gamma value for tone mapping
    
public:
    /**
     * @brief Construct a new Gamma object.
     * @param gamma Gamma value.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if gamma is less than or equal to 0.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    Gamma(double gamma, double LMax);

    /**
     * @brief Evaluate the gamma tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;
};
