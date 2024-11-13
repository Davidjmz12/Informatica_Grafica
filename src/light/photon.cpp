#include "light/photon.hpp"

Photon::Photon(const Point& position, const Vector& incident_direction, const SpectralColor& flux)
    : _position(position), _incident_direction(incident_direction), _flux(flux)
{}

Point Photon::get_position() const
{
    return this->_position;
}

Vector Photon::get_vector() const
{
    return this->_incident_direction;
}

SpectralColor Photon::get_flux() const
{
    return this->_flux;
}

double Photon::operator[](const size_t index) const
{
    return this->_position[index];
}
