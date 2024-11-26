#pragma once

#include <array>
#include <string>
#include <memory>
#include <functional>

#include "color/colorRGB.hpp"
#include "color/CIE_1931_nvidia.hpp"

#ifdef SPECTRAL_COLOR
class Color{
private:

    static constexpr size_t SIZE = 32; ///> Number of channels

    std::array<double,SIZE> _channels{}; ///> Array to store color components

    static constexpr std::array<double, SIZE> WAVELENGTHS = {
        380.00, 392.90, 405.81, 418.71, 431.61, 444.52, 457.42, 470.32, 
        483.23, 496.13, 509.03, 521.94, 534.84, 547.74, 560.65, 573.55, 
        586.45, 599.35, 612.26, 625.16, 638.06, 650.97, 663.87, 676.77, 
        689.68, 702.58, 715.48, 728.39, 741.29, 754.19, 767.10, 780.00, 
    };  ///> Wavelengths of the channels

    static constexpr double increment = 12.9; ///> Increment between channels

public:
    
    Color();

    /**
     * @brief Construct a new Color object given an array of 32 channels.
     * 
     * @param channels_32 The array of 32 channels.
     * @throw invalid_argument if any channel is negative.
     */
    explicit Color(const std::array<double,32>& channels_32);

    /**
     * @brief Construct a new Color object given an array of 16 channels.
     * 
     * @param channels_16 The array of 16 channels.
     * @throw invalid_argument if any channel is negative.
     */
    explicit Color(const std::array<double,16>& channels_16);

    /**
     * @brief Construct a new Color object given an array of 8 channels.
     * 
     * @param channels_8 The array of 8 channels.
     * @throw invalid_argument if any channel is negative.
     */
    explicit Color(const std::array<double,8>& channels_8);

    /**
     * @brief Construct a new Color object given an RGB triplet.
     * 
     * @param rgb The RGB triplet.
     * @throw invalid_argument if any channel is negative.
     */
    explicit Color(const std::array<double,3>& rgb);

    /**
     * @brief Construct a new Color object given a function that maps wavelengths to intensities.
     * 
     * @param f The function to generate the color.
     * @throws invalid_argument if the returns a negative value for any wavelengths.
     */
    explicit Color(const std::function<double(double)>& f);
    
    /**
     * @brief Construct a new Color object given a constant intensity.
     * 
     * @param intensity The intensity of the color.
     */
    explicit Color(double intensity);

    /**
     * @brief Convert the color to RGB encoding.
     * 
     * @return The color in RGB encoding.
     */
    [[nodiscard]] ColorRGB to_rgb() const;
    

    /**
     * @brief Apply tone mapping to the color.
     * 
     * @param t Tone mapping type.
     * @return Tone-mapped color.
     */
    [[nodiscard]] Color apply_tone_mapping(const std::unique_ptr<ToneMapping>& t) const;


    /**
     * @brief Get string representation of the color.
     * 
     * @return String representation of the color.
     */
    [[nodiscard]] std::string to_string() const;

    /**
     * @brief Computes the luminance of the color as the mean of the color channels.
     * 
     * @return The luminance of the color.
     */
    [[nodiscard]] double luminance_mean() const;

    /**
     * @brief Computes the luminance of the color as the maximum of the color channels.
     * 
     * @return The luminance of the color.
     */
    [[nodiscard]] double luminance_max() const;

    /**
     * @brief Accesses the color component at the specified index.
     * 
     * @param index The index of the color component.
     * @return The value of the color component at the specified index.
     */
    double operator[](size_t index) const;

    /**
     * @brief Adds two colors.
     * 
     * @param c The color to add.
     * @return The result of adding the two colors.
     */
    Color operator+(const Color& c) const;

    /**
     * @brief Multiplies two colors.
     * 
     * @param c The color to multiply.
     * @return The result of multiplying the two colors.
     */
    Color operator*(const Color& c) const;

    /**
     * @brief Multiplies the color by a scalar.
     * 
     * @param f The scalar to multiply by.
     * @return The result of multiplying the color by the scalar.
     */
    Color operator*(double f) const;

    /**
     * @brief Divides the color by a scalar.
     * 
     * @param f The scalar to divide by.
     * @return The result of dividing the color by the scalar.
     */
    Color operator/(double f) const;

    /**
     * @brief Outputs the color to an output stream.
     * 
     * @param os The output stream.
     * @param g The color to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Color& g);

    /**
     * @brief Checks if two colors are equal.
     * 
     * @param c The color to compare with.
     * @return True if the colors are equal, false otherwise.
     */
    bool operator==(const Color& c) const;

    /**
     * @brief Checks if all channels of the color are less than or equal to a scalar.
     * 
     * @param f The scalar to compare with.
     * @return True if the color is less than or equal to the scalar, false otherwise.
     */
    bool operator<=(double f) const;

};

#else

/**
 * @typedef Color
 * @brief Defines Color as ColorRGB when SPECTRAL_COLOR is not defined.
 */
using Color = ColorRGB;

#endif  // SPECTRAL_COLOR

