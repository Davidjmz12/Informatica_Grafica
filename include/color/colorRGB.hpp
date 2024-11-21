#pragma once

#include <array>
#include <memory>
#include <functional>

#include "color/tone_mapping/tone_mapping.hpp"
#include "global_config/constants.hpp"


using SC3 = std::array<double,3>;
using SC8 = std::array<double,8>;
using SC16 = std::array<double,16>;
using SC32 = std::array<double,32>;


class ColorRGB
{
private:

    std::array<double, 3> _colors; ///< Array to store color components

public:

    ColorRGB();

    explicit ColorRGB(const std::array<double,32>& channels_32);

    explicit ColorRGB(const std::array<double,16>& channels_16);

    explicit ColorRGB(const std::array<double,8>& channels_8);

    explicit ColorRGB(const std::array<double,3>& rgb);

    explicit ColorRGB(const std::function<double(double)>& f);

    explicit ColorRGB(double intensity);

    [[nodiscard]]  ColorRGB to_rgb() const;

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


    [[nodiscard]] double luminance_mean() const;

    [[nodiscard]] double luminance_max() const;

    /* Operators */

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    double operator[](size_t index) const;

    ColorRGB operator*(const ColorRGB& c) const;
    
    ColorRGB operator+(const ColorRGB& c) const;

    ColorRGB operator*(double f) const;

    ColorRGB operator/(double f) const;

    /**
     * @brief Output the color to an output stream.
     * @param os Output stream.
     * @param g ColorRGB to output.
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorRGB& g);


    bool operator<=(const ColorRGB& c) const;

    /**
     * @brief Compare two colors for equality.
     * @param l ColorRGB to compare with.
     * @return True if colors are equal, false otherwise.
     */
    bool operator==(const ColorRGB& l) const;

    bool operator<=(double f) const;

};