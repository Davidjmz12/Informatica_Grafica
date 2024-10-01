#ifndef TONE_MAPPING
#define TONE_MAPPING

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>


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
     * @brief Retrieves the maximum luminance value.
     * 
     * This function returns the highest luminance value that can be achieved.
     * It is useful for tone mapping and other graphics operations where the
     * maximum brightness level needs to be known.
     * 
     * @return float The maximum luminance value.
     */
    float max_luminance() const;

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
    float evaluate(float l_in) const;


    /**
     * @brief Overloads the << operator to output the ToneMapping object to an ostream.
     * 
     * @param os The output stream to which the ToneMapping object will be written.
     * @param g The ToneMapping object to be written to the output stream.
     * @return std::ostream& The output stream after the ToneMapping object has been written.
     */
    friend std::ostream& operator<<(std::ostream& os,const ToneMapping& g);

};

#endif