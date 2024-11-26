#pragma once

#include <array>
#include <memory>
#include <functional>

#include "color/tone_mapping/tone_mapping.hpp"
#include "global_config/constants.hpp"


using SC3 = std::array<double,3>; ///< Array of 3 doubles to represent a Color
using SC8 = std::array<double,8>; ///< Array of 8 doubles to represent a Color
using SC16 = std::array<double,16>; ///< Array of 16 doubles to represent a Color
using SC32 = std::array<double,32>; ///< Array of 32 doubles to represent a Color


/**
 * @class ColorRGB
 * @brief Represents a color in the RGB color space.
 * 
 * The ColorRGB class provides various constructors to create colors from different representations, 
 * as well as methods to manipulate and convert colors.
 */
class ColorRGB
{
private:

    std::array<double, 3> _colors; ///< Array to store color components

public:

    /**
     * @brief Default constructor for the ColorRGB class.
     * 
     * Initializes the color to black (all channels set to zero).
     */
    ColorRGB();

    /**
     * @brief Construct a new ColorRGB object given an array of 32 channels.
     * 
     * @param channels_32 The array of 32 channels.
     */
    explicit ColorRGB(const std::array<double,32>& channels_32);

    /**
     * @brief Construct a new ColorRGB object given an array of 16 channels.
     * 
     * @param channels_16 The array of 16 channels.
     */
    explicit ColorRGB(const std::array<double,16>& channels_16);

    /**
     * @brief Construct a new ColorRGB object given an array of 8 channels.
     * 
     * @param channels_8 The array of 8 channels.
     */
    explicit ColorRGB(const std::array<double,8>& channels_8);

    /**
     * @brief Construct a new ColorRGB object given an RGB triplet.
     * 
     * @param rgb The RGB triplet.
     */
    explicit ColorRGB(const std::array<double,3>& rgb);

    /**
     * @brief Construct a new ColorRGB object given a function that maps wavelengths to intensities.
     * 
     * @param f The function to generate the color.
     */
    explicit ColorRGB(const std::function<double(double)>& f);

    /**
     * @brief Construct a new ColorRGB object given a constant intensity.
     * 
     * @param intensity The intensity of the color.
     */
    explicit ColorRGB(double intensity);

    /**
     * @brief Get the color components.
     * @return Array of color components.
     */
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

    /**
     * @brief Compute the mean luminance of the color.
     * @return The mean luminance of the color.
     */
    [[nodiscard]] double luminance_mean() const;

    /**
     * @brief Compute the maximum luminance of the color.
     * @return The maximum luminance of the color.
     */
    [[nodiscard]] double luminance_max() const;

    /**
     * @brief Access color components by index.
     * @param index Index of the color component.
     * @return Value of the color component at the given index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    double operator[](size_t index) const;

    /** 
     * @brief Multiply two colors.
     * 
     * @param c Color to multiply.
     * @return Result of multiplying the two colors.
     */
    ColorRGB operator*(const ColorRGB& c) const;
    
    /**
     * @brief Add two colors.
     * 
     * @param c Color to add.
     * @return Result of adding the two colors.
     */
    ColorRGB operator+(const ColorRGB& c) const;

    /**
     * @brief Multiply a color by a scalar.
     * 
     * @param f Scalar to multiply by.
     * @return Result of multiplying the color by the scalar.
     */
    ColorRGB operator*(double f) const;

    /**
     * @brief Divide a color by a scalar.
     * 
     * @param f Scalar to divide by.
     * @return Result of dividing the color by the scalar.
     */
    ColorRGB operator/(double f) const;

    /**
     * @brief Output the color to an output stream.
     * @param os Output stream.
     * @param g ColorRGB to output.
     * @return Output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const ColorRGB& g);


    /**
     * @brief Compare two colors for equality.
     * @param l ColorRGB to compare with.
     * @return True if colors are equal, false otherwise.
     */
    bool operator<=(const ColorRGB& c) const;

    /**
     * @brief Compare two colors for equality.
     * @param l ColorRGB to compare with.
     * @return True if colors are equal, false otherwise.
     */
    bool operator==(const ColorRGB& l) const;

    /**
     * @brief Compare all color components to a scalar.
     * @param f Scalar to compare with.
     * @return True if all color components are less than or equal to the scalar, false otherwise.
     */
    bool operator<=(double f) const;

};