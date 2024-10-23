#include "properties/property.hpp"

Property::Property()
    : _color()
{}

Property::Property(Color color)
    : _color(color)
{}

Color Property::get_color() const
{
    return this->_color;
}