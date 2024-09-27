#ifndef COLOR_MAP
#define COLOR_MAP

#include <vector>

#include "color.hpp"

using std::vector;


/**
 * @class ColorMap
 * @brief A class to represent and manipulate a 2D map of colors.
 */
class ColorMap {
    private:
    
        vector<vector<Color>> _colors; ///< 2D vector to store colors.
        ColorEncoding _encode; ///< Encoding type of the colors.

    public:

        ColorMap();

        /**
         * @brief Construct a new ColorMap object.
         * @param colors 2D vector of colors.
         * @param encode Encoding type of the colors.
         */
        ColorMap(vector<vector<Color>> colors, ColorEncoding encode);

        /**
         * @brief Convert all colors in the map from RGB to HSV.
         * @return ColorMap with colors in HSV encoding.
         */
        ColorMap RGB_to_HSV() const;

        /**
         * @brief Convert all colors in the map from HSV to RGB.
         * @return ColorMap with colors in RGB encoding.
         */
        ColorMap HSV_to_RGB() const;

        /**
         * @brief Apply a tone mapping to all colors in the map.
         * @param t Tone mapping to apply.
         * @return ColorMap with tone-mapped colors.
         */
        ColorMap apply_tone_mapping(ToneMapping t) const;

        /**
         * @brief Get the colors in the map.
         * @return 2D vector of colors.
         */
        vector<vector<Color>> colors() const;

        /**
         * @brief Compare two color maps for equality.
         * @param l Color map to compare with.
         * @return True if color maps are equal, false otherwise.
         */
        bool operator==(ColorMap l) const;

        /**
         * @brief Output the ColorMap to an output stream.
         * @param os Output stream.
         * @param g ColorMap to output.
         * @return Output stream.
         */
        friend std::ostream& operator<<(std::ostream& os,const Color& g);
        
};

#endif