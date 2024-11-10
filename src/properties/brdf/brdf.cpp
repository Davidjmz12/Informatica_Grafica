#include "properties/brdf/brdf.hpp"

BRDF::BRDF(SpectralColor k)
    : _k(k)
{}

BRDF::BRDF()
    : _k(SpectralColor())
{}

SpectralColor BRDF::get_color() const
{
    return this->_k;
}