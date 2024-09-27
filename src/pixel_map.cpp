
#include "pixel_map.hpp"

PixelMap::PixelMap(vector<vector<Pixel>> pixels, ColorEncode encode):
    _pixels(pixels),_type(encode){};


bool PixelMap::RGB_to_HSV()
{
    if(this->_type == HSV)
    {
        return false;
    }

    for(auto i: this->_pixels)
    {
        for (Pixel pixel: i)
        {
            pixel.RGB_to_HSV();
        }
    }    

    return true;

}

bool PixelMap::HSV_to_RGB()
{
    if(this->_type == RGB)
    {
        return false;
    }
    
    for(auto i: this->_pixels)
    {
        for (Pixel pixel: i)
        {
            pixel.HSV_to_RGB();
        }
    }
    return true;
}