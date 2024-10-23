#pragma once

#include "color.hpp"

class Property
{
private:
    Color _color;

public:

    Property();
    Property(Color color);


    Color get_color() const;
};
