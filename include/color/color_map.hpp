#pragma once

#include <vector>
#include <iomanip>

#include "color/spectral_color.hpp"

using std::vector;


/**
 * @class ColorMap
 * @brief A class to represent and manipulate a 2D map of colors.
 */
class ColorMap {
    private:
    
        vector<vector<SpectralColor>> _colors; ///< 2D vector to store colors.

    public:

        ColorMap();

        /**
         * @brief Construct a new ColorMap object.
         * @param colors 2D vector of colors.
         * @param encode Encoding type of the colors.
         * @throw invalid_argument If the colors are not equally encoded.
         */
        ColorMap(vector<vector<SpectralColor>> colors);

        /**
         * @brief Apply a tone mapping to all colors in the map.
         * @param t Tone mapping to apply.
         * @return ColorMap with tone-mapped colors.
         */
        ColorMap apply_tone_mapping(ToneMapping* t) const;

        

        /**
         * @brief Get the colors in the map.
         * @return 2D vector of colors.
         */
        vector<vector<SpectralColor>> colors() const;

        /**
         * @brief Compare two color maps for equality.
         * @param l Color map to compare with.
         * @return True if color maps are equal, false otherwise.
         */
        bool operator==(ColorMap l) const;


        std::string to_string() const;

        /**
         * @brief Output the ColorMap to an output stream.
         * @param os Output stream.
         * @param g ColorMap to output.
         * @return Output stream.
         */
        friend std::ostream& operator<<(std::ostream& os,const ColorMap& g);
        
};
