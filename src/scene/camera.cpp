#include "scene/camera.hpp"

Camera::Camera(Base base, std::array<int,2> resolution)
    : _screen_base(base), _resolution(resolution)
{}

SpatialElement* Camera::transform_to_canonical(const SpatialElement* s) const
{
    return this->_screen_base.coord_into_canonical(s);
}

std::array<int,2> Camera::get_resolution() const
{
    return this->_resolution;
}

Base Camera::get_screen_base() const
{
    return this->_screen_base;
}


std::ostream& operator<<(std::ostream& os, Camera c)
{
    os << "Camera:" << c.to_string() << std::endl;
    return os;
}

std::string Camera::to_string()
{
    std::stringstream ss;
    ss << "\n\tResolution: " << this->_resolution[0] << "x" << this->_resolution[1]
       << "\n\tScreen Base: " << this->_screen_base.to_string();
    return ss.str();
}
