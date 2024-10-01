/**
 * @file color.hpp
 * @brief Defines a color class and color encoding types.
 * @authors Davidjmz12 DavidTizne
 * @date 01/10/2024
 *
 * This file contains the definition of the Color class, which represents
 * a color in RGB or HSV encoding.
*/

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <string>
#include <iostream>
#include <array>

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

    std::array<float, 3> _colors; ///< Array to store color components
    ColorEncoding _type; ///< Encoding type of the color
    std::array<float, 3> _range; ///< Range of the color components

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

    static const std::array<float, 3> RGB_STANDARD_RANGE; ///< Standard range for RGB colors
    static const std::array<float, 3> HSV_STANDARD_RANGE; ///< Standard range for HSV colors

    /**
     * @brief Construct a new Color object with a range from 0 to 1.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param type Encoding type of the color.
     * @throws std::invalid_argument if any color component is out of the standard ranges.
     */
    Color(std::array<float, 3> colors, std::array<float, 3> range , ColorEncoding type);

    /**
     * @brief Generates an array of three float values, each equal to the input value.
     * 
     * @param f The float value to be repeated in the array.
     * @return std::array<float, 3> An array containing three float values, all equal to the input value.
     */
    static std::array<float, 3> same_range(float f);

    /**
     * @brief Normalizes the color values.
     * 
     * @return A normalized Color object.
     */
    Color normalize() const;

    /**
     * @brief Changes the color range to a new specified range.
     * 
     * This function takes a new range specified by an array of three float values
     * and returns a Color object with the updated range.
     * 
     * @param new_range An array of three float values representing the new color range.
     * @return Color A Color object with the updated range.
     */
    Color change_range(std::array<float, 3> new_range) const;

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::out_of_range if the index is out of bounds.
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
     * @brief Get the encoding type of the color.
     * @return Encoding type of the color.
     */
    ColorEncoding get_type() const;

    /**
     * @brief Apply tone mapping to the color.
     * @param t Tone mapping type.
     * @return Tone-mapped color.
     * @throws std::invalid_argument if the color is in RGB encoding.
     * @throws std::invalid_argument if the tone mapping maximum value is greater than the maximum luminance value.
     */
    Color apply_tone_mapping(ToneMapping t) const;

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