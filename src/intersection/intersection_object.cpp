#include "intersection/intersection_object.hpp"

IntersectionObject::IntersectionObject(double distance, Vector normal, Point intersection_point, BRDF brdf, Ray ray, bool is_entering)
    : Intersection(distance, intersection_point, ray), _normal(normal), _brdf(brdf), _is_entering(is_entering)
{}

IntersectionObject::IntersectionObject()
{}

Vector IntersectionObject::get_normal() const
{
    return this->_normal;
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

void IntersectionObject::set_u_v(const double u, const double v)
{
    this->_u = u;
    this->_v = v;
}

Color IntersectionObject::eval_brdf(Color light, Vector w_i, BRDFType type) const
{
    double const_ = (BRDF::is_delta(type) ? 1.0 : M_PI);
    return this->_brdf.eval(light/const_, w_i, this->get_ray().get_direction()*(-1), 
        this->_intersection_point, this->_normal, this->get_ray().get_refraction_coefficient(), this->_u, this->_v,  type);
}

BRDFType IntersectionObject::sample_ray(Ray& sampled_ray)
{
    return this->_brdf.sample_ray(this->_ray.get_direction()*(-1), 
        this->_intersection_point, this->_normal, 
        this->get_ray().get_refraction_coefficient(), sampled_ray,
        this->_is_entering);
}

bool IntersectionObject::operator==(const IntersectionObject i) const
{
    return  eqD(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_intersection_point == i._intersection_point &&
            this->_is_entering == i._is_entering;
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