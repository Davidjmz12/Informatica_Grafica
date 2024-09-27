#ifndef COLOR_MAP
#define COLOR_MAP

#include <vector>

#include "color.hpp"

using std::vector;

class ColorMap {
    private:
        vector<vector<Color>> _colors;
        ColorEncoding _encode;

    public:
        ColorMap(vector<vector<Color>> colors, ColorEncoding encode);

        ColorMap RGB_to_HSV() const;
        ColorMap HSV_to_RGB() const;

        vector<vector<Color>> colors() const;

        bool operator==(ColorMap l) const;

        friend std::ostream& operator<<(std::ostream& os,const Color& g);
        
};

#endif