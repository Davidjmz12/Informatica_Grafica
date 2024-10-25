#pragma once

#include "color.hpp"
#include "properties/brdf/diffuse_brdf.hpp"

class Property
{
private:
    Color _color;
    BRDF* _brdf;

public:

    Property();
    Property(Color color);
    Property(Color color, BRDF* brdf);


    Color get_color() const;
    BRDF* get_BRDF() const;

    friend std::ostream& operator<<(std::ostream& os, const Property& p);

    std::string to_string() const;

};
