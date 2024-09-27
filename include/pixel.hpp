#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cmath>
#include <string>
#include <iostream>

const float range=255.0F;
const float threshold=10e-6;
enum ColorEncode {
    RGB,
    HSV
};


class Pixel
{
private:
    float colors[3];
    ColorEncode type;

public:
    Pixel(float _red, float _green, float _blue, ColorEncode _type);

    float operator[](int index) const;

    float max();
    float min();

    Pixel normalize() const;
    Pixel RGB_to_HSV() const;
    Pixel HSV_to_RGB() const;


    bool operator==(Pixel l) const;

    friend std::ostream& operator<<(std::ostream& os,const Pixel& g);

};

#endif