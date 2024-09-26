#ifndef PIXEL_MAP
#define PIXEL_MAP

#include <vector>

#include "pixel.hpp"

using std::vector;

enum ColorEncode {
    RGB,
    HSV
};

class PixelMap {
    private:
        vector<vector<Pixel>> _pixels;
        ColorEncode _type;

    public:
        PixelMap();
        PixelMap(vector<vector<Pixel>> pixels, ColorEncode encode);

        bool RGB_to_HSV();
        bool HSV_to_RGB();

        Pixel get(int i, int j);
};

#endif