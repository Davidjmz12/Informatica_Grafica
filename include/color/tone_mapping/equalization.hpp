#pragma once

#include "color/tone_mapping/tone_mapping.hpp"

/**
 * @class ToneMapping
 * @brief A class to represent and apply the equalization and the clamping
 * technique.
 */
class Equalization : public ToneMapping
{
private:
    double _V; ///< Clamping value for tone mapping

public:
    /**
     * @brief Construct a new Equalization object.
     * @param V Clamping value.
     * @throws std::invalid_argument if V is greater than LMax or less than 0.
     */
    Equalization(double V);

    /**
     * @brief Evaluate the equalization and the clamping tone mapping
     * for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    double evaluate(double l_in) const;
};