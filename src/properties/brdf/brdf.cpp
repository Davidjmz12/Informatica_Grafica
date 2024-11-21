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