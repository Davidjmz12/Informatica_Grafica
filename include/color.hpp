#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <string>
#include <iostream>

#include "tone_mapping.hpp"
#include "constants.hpp"

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
    float max() const;

    /**
     * @brief Get the minimum value among the color components.
     * @return Minimum value among the color components.
     */
    float min() const;


public:

    /**
     * @brief Construct a new Color object with a range from 0 to 1.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param type Encoding type of the color.
     * @throws std::invalid_argument if any color component is out of the standard ranges.
     */
    Color(float c1, float c2, float c3, ColorEncoding type);

    /**
     * @brief Construct a new RGB Color object with a non-arbitrary positive range.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param max_value_rgb Maximum value of the color components.
     * @throws std::invalid_argument if any color component is out of the given range.
     */
    static Color RGBNormalized(float c1, float c2, float c3, float max_value_rgb);

    /**
     * @brief Construct a new HSV Color object with a non-arbitrary positive range.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param max_value_h Maximum value of the hue component.
     * @param max_value_sv Maximum value of the saturation and value components.
     * @throws std::invalid_argument if any color component is out of the given range.
     */
    static Color HSVNormalized(float c1, float c2, float c3, float max_value_h, float max_value_sv);

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::invalid_argument if the index is out of bounds.
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
     * @throws std::invalid_argument if the color is in RGB encoding.
     * @throws std::invalid_argument if the tone mapping maximum value is greater than the maximum luminance value.
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