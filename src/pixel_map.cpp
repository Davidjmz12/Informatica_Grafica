#include "pixel_map.hpp"

PixelMap::PixelMap(){}

PixelMap::PixelMap(vector<vector<Pixel>> pixels, ColorEncode encode)
{
    
}

std::ostream& operator<<(std::ostream& os,const PixelMap pm)
{
    os << "Hola";
    return os;
}