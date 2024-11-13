#pragma once

#include <array>
#include <memory>

#include "color/tone_mapping/tone_mapping.hpp"
#include "global_config/constants.hpp"


class ColorRGB
{
private:

    std::array<double, 3> _colors; ///< Array to store color components

public:

    explicit ColorRGB(const std::array<double, 3>& colors);
    ColorRGB();

    [[nodiscard]] ColorRGB normalize(double max_value) const;

    /**
     * @brief Standardizes the color values.
     * 
     * @return A standardized ColorRGB object.
     */
    [[nodiscard]] ColorRGB standardize(double max_value) const;

    /**
     * @brief Apply tone mapping to the color.
     * @param t Tone mapping type.
     * @param new_resolution New resolution of the color.
     * @return Tone-mapped color.
     * @throws std::invalid_argument if the color is in RGB encoding.
     * @throws std::invalid_argument if the tone mapping maximum value is greater than the maximum luminance value.
     */
    [[nodiscard]] ColorRGB apply_tone_mapping(const std::unique_ptr<ToneMapping>& t, size_t new_resolution) const;


    /**
     * @brief Get string representation of the color.
     * @return String representation of the color.
     */
    [[nodiscard]] std::string to_string() const;


    /* Operators */

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    double operator[](size_t index) const;


    /**
     * @brief Compare two colors for equality.
     * @param l ColorRGB to compare with.
     * @return True if colors are equal, false otherwise.
     */
    bool operator==(const ColorRGB& l) const;

    /**
     * @brief Output the color to an output stream.
     * @param os Output stream.
     * @param g ColorRGB to output.
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorRGB& g);


    ColorRGB operator*(const ColorRGB& c) const;
    
    ColorRGB operator+(const ColorRGB& c) const;

    ColorRGB operator*(double f) const;

    ColorRGB operator/(double f) const;

};
