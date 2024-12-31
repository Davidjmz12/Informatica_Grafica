#include "properties/brdf/brdf.hpp"

BRDF::BRDF(Color k)
    : _k(k)
{}

BRDF::BRDF()
    : _k(Color())
{}

Color BRDF::get_color() const
{
    return this->_k;
}

void BRDF::set_color(Color k)
{
    this->_k = k;
}