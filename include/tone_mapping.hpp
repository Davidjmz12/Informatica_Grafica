#ifndef TONE_MAPPING2
#define TONE_MAPPING2

#include <stdexcept>
#include <math.h>

/**
 * @class ToneMapping
 * @brief A class to represent and apply various tone mapping techniques.
 */
class ToneMapping
{
protected:
    float _LMax; ///< Maximum luminance value for tone mapping

public:
    /**
     * @brief Construct a new ToneMapping object.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    ToneMapping(float LMax);

    /**
     * @brief Evaluate the tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    virtual float evaluate(float l_in) const = 0;

    /**
     * @brief Retrieves the maximum luminance value.
     * 
     * This function returns the highest luminance value that can be achieved.
     * It is useful for tone mapping and other graphics operations where the
     * maximum brightness level needs to be known.
     * 
     * @return The maximum luminance value.
     */
    float max_luminance() const;

};


// -----------------------------------------------------
//                      CLAMPING
// -----------------------------------------------------

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
    Clamping(float LMax);

    /**
     * @brief Evaluate the clamping tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in) const;

};


// -----------------------------------------------------
//                      EQUALIZATION
// -----------------------------------------------------

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
    Equalization(float LMax);

    /**
     * @brief Evaluate the equalization tone mapping for a given
     * luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in) const;
};


// -----------------------------------------------------
//              EQUALIZATION CLAMPING
// -----------------------------------------------------

/**
 * @class ToneMapping
 * @brief A class to represent and apply the equalization and the clamping
 * technique.
 */
class EqualizationClamping : public ToneMapping
{
private:
    float _V; ///< Clamping value for tone mapping

public:
    /**
     * @brief Construct a new EqualizationClamping object.
     * @param V Clamping value.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if V is greater than LMax or less than 0.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    EqualizationClamping(float V, float LMax);

    /**
     * @brief Evaluate the equalization and the clamping tone mapping
     * for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in) const;
};


// -----------------------------------------------------
//                      GAMMA
// -----------------------------------------------------

/**
 * @class ToneMapping
 * @brief A class to represent and apply the gamma technique.
 */
class Gamma : public ToneMapping
{
private:
    float _gamma;   ///< Gamma value for tone mapping
    
public:
    /**
     * @brief Construct a new Gamma object.
     * @param gamma Gamma value.
     * @param LMax Maximum luminance value.
     * @throws std::invalid_argument if gamma is less than or equal to 0.
     * @throws std::invalid_argument if LMax is less than or equal to 0.
     */
    Gamma(float gamma, float LMax);

    /**
     * @brief Evaluate the gamma tone mapping for a given luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in) const;
};


// -----------------------------------------------------
//                  GAMMA CLAMPING
// -----------------------------------------------------

/**
 * @class ToneMapping
 * @brief A class to represent and apply the gamma and the clamping technique.
 */
class GammaClamping : public ToneMapping
{
private:
    float _gamma;   ///< Gamma value for tone mapping
    float _V;       ///< Clamping value for tone mapping
    
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
    GammaClamping(float gamma, float V, float LMax);

    /**
     * @brief Evaluate the gamma and the clamping tone mapping for a given
     * luminance value.
     * @param l_in Input luminance value.
     * @return Mapped luminance value.
     */
    float evaluate(float l_in) const;
};



class Drago : public ToneMapping
{
public:
    Drago(float LMax);

    float evaluate(float l_in) const;
};


class Logarithmic : public ToneMapping
{
private:
    float _alpha;
    
public:
    Logarithmic(float LMax, float alpha);

    float evaluate(float l_in) const;
};


#endif