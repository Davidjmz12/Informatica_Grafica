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

bool IntersectionObject::operator==(const IntersectionObject i) const
{
    return  eqD(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_intersection_point == i._intersection_point &&
            this->_is_entering == i._is_entering;
}

SpectralColor IntersectionObject::evalRenderEquation(SpectralColor power_light, Point point_light) const
{

    Vector c1_x = point_light-this->_intersection_point;
    SpectralColor Lwi = power_light/pow(c1_x.norm(),2);
    SpectralColor brdf = this->eval_brdf(c1_x.normalize());
    double cosine = fabs(this->_normal.dot(c1_x.normalize()));

    SpectralColor results = Lwi*brdf*cosine;

    return Lwi*brdf*cosine;  
}

SpectralColor IntersectionObject::eval_brdf(Vector w_i) const
{
    return this->_properties.get_BRDF()->eval(w_i, this->get_ray().get_direction()*(-1), 
        this->_intersection_point, this->_normal, this->get_ray().get_refraction_coefficient());
}

bool IntersectionObject::sample_ray(Ray& sampled_ray) const
{
    return this->_properties.get_BRDF()->sample_ray(this->_ray.get_direction()*(-1), 
        this->_intersection_point, this->_normal, 
        this->get_ray().get_refraction_coefficient(), sampled_ray);
}

std::ostream& operator<<(std::ostream& os, const IntersectionObject& i)
{
    os << i.to_string();
    return os;
}

std::string IntersectionObject::to_string() const
{
    return "IntersectionObject: " + this->_intersection_point.to_string() + "\n" + std::to_string(this->_distance) + "\n" + this->_normal.to_string();
}