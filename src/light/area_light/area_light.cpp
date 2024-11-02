#include "light/area_light/area_light.hpp"

AreaLight::AreaLight(Geometry* shape, SpectralColor power)
    : _shape(shape), _power(power)
{}

bool AreaLight::intersect_with_ray(const Ray& r, IntersectionLight& intersection) const
{
    // Compute the intersection with the box
    IntersectionObject intersectionObject = IntersectionObject();
    bool intersects = this->_shape->intersect_with_ray(r, intersectionObject);

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

std::string AreaLight::to_string() const
{
    return  "Area Light:\nPower: " + this->_power.to_string() +
            "\nShape:\n" + this->_shape->to_string() + "\n";
}