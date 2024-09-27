#ifndef PIXEL_MAP
#define PIXEL_MAP

#include <vector>
#include <iostream>

#include "pixel.hpp"
#include "tone_mapping.hpp"

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

        void apply_tone_mapping(ToneMapping t);

        friend std::ostream& operator<<(std::ostream& os,const PixelMap pm);
};

#endif