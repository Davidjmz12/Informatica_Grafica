#ifndef TONE_MAPPING
#define TONE_MAPPING

#include <cmath>
#include <stdexcept>

/**
 * @class ToneMapping
 * @brief A class to represent and apply various tone mapping techniques.
 */
class ToneMapping
{
private:
    float _gamma; ///< Gamma value for tone mapping
    float _V; ///< Clamping value for tone mapping
    float _LMax; ///< Maximum luminance value for tone mapping

    /**
     * @brief Construct a new ToneMapping object.
     * @param gamma Gamma value.
     * @param V Clamping value.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if V is greater than LMax.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     * @throws std::invalid_argument if gamma is less than or equal to 0.
     */
    ToneMapping(float gamma, float V, float LMax);

public:

    /**
     * @brief Create a ToneMapping object using clamping technique.
     * @param LMax Maximum luminance value.
     * @return ToneMapping object.
     */
    static ToneMapping clamping(float LMax);

    /**
     * @brief Create a ToneMapping object using equalization technique.
     * @param LMax Maximum luminance value.
     * @return ToneMapping object.
     */
    static ToneMapping equalization(float LMax);
    /**
     * @brief Create a ToneMapping object using equalization and clamping technique.
     * @param V Clamping value.
     * @param LMax Maximum luminance value.
     * @return ToneMapping object.
     */
    static ToneMapping equalization_clamping(float V, float LMax);

    /**
     * @brief Create a ToneMapping object using gamma correction technique.
     * @param gamma Gamma value.
     * @param LMax Maximum luminance value.
     * @return ToneMapping object.
     */
    static ToneMapping gamma(float gamma, float LMax);

    /**
     * @brief Create a ToneMapping object using gamma correction and clamping technique.
     * @param gamma Gamma value.
     * @param V Clamping value.
     * @param LMax Maximum luminance value.
     * @return ToneMapping object.
     */
    static ToneMapping gamma_clamping(float gamma, float V, float LMax);

    /**
     * @brief Evaluate the tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in);

};

#endif