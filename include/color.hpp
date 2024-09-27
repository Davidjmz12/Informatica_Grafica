#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <string>
#include <iostream>

#include "tone_mapping.hpp"

const float range=255.0F; // Range of RGB system
const float threshold=10e-6; // Threshold for comparing colors

/**
 * @enum ColorEncoding
 * @brief Enum to represent color encoding types.
 */
enum ColorEncoding {
    RGB, ///< Red, Green, Blue encoding
    HSV  ///< Hue, Saturation, Value encoding
};

/**
 * @class Color
 * @brief A class to represent and manipulate colors.
 */
class Color
{
private:

    float _colors[3]; ///< Array to store color components
    ColorEncoding _type; ///< Encoding type of the color

    /**
     * @brief Get the maximum value among the color components.
     * @return Maximum value among the color components.
     */
    float max();

    /**
     * @brief Get the minimum value among the color components.
     * @return Minimum value among the color components.
     */
    float min();

    /**
     * @brief Normalize the color components.
     * @return Normalized color.
     */
    Color normalize() const;

public:

    /**
     * @brief Construct a new Color object.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param type Encoding type of the color.
     */
    Color(float c1, float c2, float c3, ColorEncoding type);

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     */
    float operator[](int index) const;

    /**
     * @brief Convert RGB color to HSV.
     * @return Color in HSV encoding.
     */
    Color RGB_to_HSV() const;

    /**
     * @brief Convert HSV color to RGB.
     * @return Color in RGB encoding.
     */
    Color HSV_to_RGB() const;

    /**
     * @brief Apply tone mapping to the color.
     * @param t Tone mapping type.
     * @return Tone-mapped color.
     */
    Color apply_tone_mapping(ToneMapping t) const;

    /**
     * @brief Get the encoding type of the color.
     * @return Encoding type of the color.
     */
    ColorEncoding get_type() const;

    /**
     * @brief Compare two colors for equality.
     * @param l Color to compare with.
     * @return True if colors are equal, false otherwise.
     */
    bool operator==(Color l) const;

    /**
     * @brief Output the color to an output stream.
     * @param os Output stream.
     * @param g Color to output.
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Color& g);
};

#endif