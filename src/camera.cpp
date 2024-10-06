#include "camera.hpp"

Camera::Camera(Base base, float width, float height, float distance)
    : _base(base), _width(width), _height(height), _distance(distance)
{
    if (width <= 0 || height <= 0 || distance <= 0)
        throw std::invalid_argument("Width, height and distance must be positive numbers.");
}

Ray Camera::trace_ray(float x, float y) const
{
    return Ray( this->_base.get_center(),
                (Point)this->_base.coord_into_canonical(
                    new Point(x,y,this->_distance)) -
                    this->_base.get_center());
}

Color Camera::compute_pixel_color(int x, int y, int k) const
{
    return Color(Color::same_range(0), Color::same_range(255), RGB);
}

std::ostream& operator<<(std::ostream& os, Camera c)
{
    os << "Camera:" << std::endl;
    os << c._base << std::endl;
    os << "Dimensions: " << c._width << "x" << c._height << std::endl;
    os << "Distance: " << c._distance; 

    return os;
}
