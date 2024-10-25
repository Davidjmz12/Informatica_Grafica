#pragma once

#include "color/spectral_color.hpp"
#include "properties/brdf/diffuse_brdf.hpp"

class Property
{
private:
    SpectralColor _color;
    BRDF* _brdf;

public:

    Property();
    Property(SpectralColor color);
    Property(SpectralColor color, BRDF* brdf);


    SpectralColor get_color() const;
    BRDF* get_BRDF() const;

    friend std::ostream& operator<<(std::ostream& os, const Property& p);

    std::string to_string() const;

};
