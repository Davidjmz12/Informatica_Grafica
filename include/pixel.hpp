#ifndef PIXEL_HPP
#define PIXEL_HPP

class Pixel
{
private:
    float _colors[3];

public:
    Pixel(float red, float green, float blue);

    float operator[](int index);

};

#endif