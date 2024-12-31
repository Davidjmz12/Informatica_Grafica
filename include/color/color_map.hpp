#pragma once

#include <vector>
#include <iomanip>

#include "color/color.hpp"
#include "color/colorRGB.hpp"

using MatrixSC = std::vector<std::vector<Color>>;
using MatrixRGB = std::vector<std::vector<ColorRGB>>;


/**
 * @class ColorMap
 * @brief A class to represent and manipulate a 2D map of colors.
 */
class ColorMap {
    private:
    
        MatrixRGB _colors; ///< 2D vector to store colors.

    public:

        ColorMap();

        #ifdef SPECTRAL_COLOR
        /**
         * @brief Construct a new ColorMap object.
         * @param spectral_colors 2D vector of spectral colors.
         * @throw invalid_argument If the colors are not equally encoded.
         */
        explicit ColorMap(const MatrixSC& spectral_colors);
        #endif // SPECTRAL_COLOR
        
        explicit ColorMap(MatrixRGB colors);

        [[nodiscard]] double max() const;

        [[nodiscard]] ColorRGB get_color(size_t x, size_t y) const;

        /**
         * @brief Apply a tone mapping to all colors in the map.
         * @param t Tone mapping to apply.
         * @param new_resolution New resolution of the color map.
         * @return ColorMap with tone-mapped colors.
         */
        ColorMap apply_tone_mapping(const std::unique_ptr<ToneMapping>& t, size_t new_resolution) const;


        /**
         * @brief Get the colors in the map.
         * @return 2D vector of colors.
         */
        [[nodiscard]] MatrixRGB colors() const;

        /**
         * @brief Compare two color maps for equality.
         * @param l Color map to compare with.
         * @return True if color maps are equal, false otherwise.
         */
        bool operator==(const ColorMap& l) const;


        [[nodiscard]] std::string to_string() const;

        /**
         * @brief Output the ColorMap to an output stream.
         * @param os Output stream.
         * @param g ColorMap to output.
         * @return Output stream.
         */
        friend std::ostream& operator<<(std::ostream& os,const ColorMap& g);
        
};
