#include "intersection/intersection_object.hpp"

IntersectionObject::IntersectionObject(double distance, Vector normal, Point intersection_point, Property properties, Ray ray, bool is_entering)
    : Intersection(distance, intersection_point, ray), _normal(normal), _properties(properties), _is_entering(is_entering)
{}

IntersectionObject::IntersectionObject()
{}

Vector IntersectionObject::get_normal() const
{
    return this->_normal;
}

Property IntersectionObject::get_properties() const
{
    return this->_properties;
}

bool IntersectionObject::is_entering() const
{
    return this->_is_entering;
}

void IntersectionObject::set_is_entering(const bool is_entering)
{
    this->_is_entering = is_entering;
}

void IntersectionObject::inverse_normal()
{
    this->_normal = this->_normal*(-1);
}

void IntersectionObject::change_color(Color color)
{
    this->_properties.get_BRDF()->set_color(color);
}

bool IntersectionObject::is_delta() const
{
    return this->_properties.get_BRDF()->is_delta();
}

bool IntersectionObject::operator==(const IntersectionObject i) const
{
    return  eqD(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_intersection_point == i._intersection_point &&
            this->_is_entering == i._is_entering;
}


Color IntersectionObject::eval_brdf(Color light, Vector w_i) const
{
    double const_ = (this->is_delta() ? 1.0 : M_PI);
    return this->_properties.get_BRDF()->eval(light*const_, w_i, this->get_ray().get_direction()*(-1), 
        this->_intersection_point, this->_normal, this->get_ray().get_refraction_coefficient());
}

bool IntersectionObject::sample_ray(Ray& sampled_ray)
{
    return this->_properties.get_BRDF()->sample_ray(this->_ray.get_direction()*(-1), 
        this->_intersection_point, this->_normal, 
        this->get_ray().get_refraction_coefficient(), sampled_ray,
        this->_is_entering);
}

std::ostream& operator<<(std::ostream& os, const IntersectionObject& i)
{
    os << i.to_string();
    return os;
}

IntersectionObject IntersectionObject::min(const std::vector<IntersectionObject>& intersections)
{
    if(intersections.empty())
        throw std::invalid_argument("The vector of intersections is empty.");

    IntersectionObject min;
    for(const auto& i : intersections)
    {
        if(i < min)
            min = i;
    }

    return min;
}

std::string IntersectionObject::to_string() const
{
    return "IntersectionObject: " + this->_intersection_point.to_string() + "\n" + std::to_string(this->_distance) + "\n" + this->_normal.to_string();
}