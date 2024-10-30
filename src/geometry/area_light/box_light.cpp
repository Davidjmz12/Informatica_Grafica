#include "geometry/area_light/box_light.hpp"

BoxLight::BoxLight(Box box, SpectralColor power)
    : AreaLight(power), _box(box)
{}

bool BoxLight::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    return this->_box.intersect_with_ray(r, intersection);
}

std::string BoxLight::to_string() const
{
    return  "Box Light:\nPower: " + this->_power.to_string() +
            "\nBox:\n" + this->_box.to_string() + "\n";
}