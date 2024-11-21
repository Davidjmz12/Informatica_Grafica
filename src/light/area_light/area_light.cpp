#include "light/area_light/area_light.hpp"

AreaLight::AreaLight(std::shared_ptr<Geometry> shape, Color power)
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
                                        intersectionObject.get_int_point(),
                                        intersectionObject.get_ray());
    return true;            
}

std::string AreaLight::to_string() const
{
    return  "Area Light:\nPower: " + this->_power.to_string() +
            "\nShape:\n" + this->_shape->to_string() + "\n";
}