#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>
#include <string>
#include <iostream>

const float range=255.0F;
const float threshold=10e-6;

enum ColorEncoding {
    RGB,
    HSV
};


class Color
{
private:
    float _colors[3];
    ColorEncoding _type;

    float max();
    float min();
    Color normalize() const;

public:

    Color(float c1, float c2, float c3, ColorEncoding type);

    float operator[](int index) const;

    
    Color RGB_to_HSV() const;
    Color HSV_to_RGB() const;

    ColorEncoding get_type() const;

    bool operator==(Color l) const;

    friend std::ostream& operator<<(std::ostream& os,const Color& g);

};

#endif