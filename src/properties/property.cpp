#include "properties/property.hpp"

Property::Property(Color color):
    _color(color)
{}

Property::Property()
    : _color(Color())
{}

Color Property::get_color() const
{
    return this->_color;
}