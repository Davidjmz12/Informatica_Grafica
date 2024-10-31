#include "light/area_light/box_light.hpp"

BoxLight::BoxLight(Box box, SpectralColor power)
    : AreaLight(power), _box(box)
{}

bool BoxLight::intersect_with_ray(const Ray& r, IntersectionLight& intersection) const
{
    // Compute the intersection with the box
    IntersectionObject intersectionObject = IntersectionObject();
    bool intersects = this->_box.intersect_with_ray(r, intersectionObject);

    // Check if do not intersects
    if (!intersects)
        return false;
    
    // Construct the intersection light object
    intersection = IntersectionLight(   intersectionObject.get_distance(),
                                        this->_power,
                                        r.get_direction(),
                                        intersectionObject.get_point());
    return true;            
}

std::string BoxLight::to_string() const
{
    return  "Box Light:\nPower: " + this->_power.to_string() +
            "\nBox:\n" + this->_box.to_string() + "\n";
}