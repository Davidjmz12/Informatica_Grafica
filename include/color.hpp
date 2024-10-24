/**
 * @file color.hpp
 * @brief Defines a color class and color encoding types.
 * @authors Davidjmz12 DavidTizne
 * @date 01/10/2024
 *
 * This file contains the definition of the Color class, which represents
 * a color in RGB or HSV encoding.
*/

#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <array>

#include "tone_mapping/tone_mapping.hpp"
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

    std::array<double, 3> _colors; ///< Array to store color components
    ColorEncoding _type; ///< Encoding type of the color
    std::array<double, 3> _range; ///< Range of the color components
    
    /**
     * @brief Get the maximum value among the color components.
     * @return Maximum value among the color components.
     */
    double max() const;

    /**
     * @brief Get the minimum value among the color components.
     * @return Minimum value among the color components.
     */
    double min() const;


public:

    static const std::array<double, 3> RGB_STANDARD_RANGE; ///< Standard range for RGB colors
    static const std::array<double, 3> HSV_STANDARD_RANGE; ///< Standard range for HSV colors
    static const std::array<double, 3> RGB_255_RANGE; ///< Range for RGB colors with 255 as maximum value

    /**
     * @brief Construct a new Color object with a range from 0 to 1.
     * @param c1 First color component.
     * @param c2 Second color component.
     * @param c3 Third color component.
     * @param type Encoding type of the color.
     * @throws std::invalid_argument if any color component is out of the standard ranges.
     */
    Color(std::array<double, 3> colors, std::array<double, 3> range , ColorEncoding type);

    Color();

    /**
     * @brief Generates an array of three double values, each equal to the input value.
     * 
     * @param f The double value to be repeated in the array.
     * @return std::array<double, 3> An array containing three double values, all equal to the input value.
     */
    static std::array<double, 3> same_range(double f);

    /**
     * @brief Normalizes the color values.
     * 
     * @return A normalized Color object.
     */
    Color normalize() const;

    /**
     * @brief Changes the color range to a new specified range.
     * 
     * This function takes a new range specified by an array of three double values
     * and returns a Color object with the updated range.
     * 
     * @param new_range An array of three double values representing the new color range.
     * @return Color A Color object with the updated range.
     */
    Color change_range(std::array<double, 3> new_range) const;

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    double operator[](int index) const;

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

    std::array<double, 3> get_colors() const;
    std::array<double, 3> get_range() const;

    /**
     * @brief Apply tone mapping to the color.
     * @param t Tone mapping type.
     * @return Tone-mapped color.
     * @throws std::invalid_argument if the color is in RGB encoding.
     * @throws std::invalid_argument if the tone mapping maximum value is greater than the maximum luminance value.
     */
    Color apply_tone_mapping(ToneMapping* t) const;

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

    std::string to_string() const;

    Color operator*(Color c) const;
    
    Color operator+(Color c) const;

    Color operator*(double f) const;

    Color operator/(double f) const;
};

