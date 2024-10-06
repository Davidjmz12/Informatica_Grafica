#pragma once

#include "tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the gamma and the clamping technique.
 */
class GammaClamping : public ToneMapping
{
private:
    double _gamma;   ///< Gamma value for tone mapping
    double _V;       ///< Clamping value for tone mapping
    
public:
    /**
     * @brief Construct a new GammaClamping object.
     * @param gamma Gamma value.
     * @param V Clamping value.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if gamma is less than or equal to 0.
     * @throws std::invalid_argument if V is greater than LMax or less than 0.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    GammaClamping(double gamma, double V, double LMax);

    /**
     * @brief Evaluate the gamma and the clamping tone mapping for a given
     * luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;
};
