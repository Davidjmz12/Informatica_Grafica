#include "geometry/face.hpp"

Face::Face(Vector normal, Vector u, Vector v, Point point, Property properties)
    :  Geometry(properties), _normal(normal), _point(point)
{
    if (neqD(normal.dot(u),0) || neqD(normal.dot(v),0))
        throw std::invalid_argument("The vectors u and v must be perpendicular to the normal vector.");
    if (!normal.is_base(u,v))
        throw std::invalid_argument("The vectors u, v and the norm must be a R^3 base.");
    
    this->_sizes = {u.norm(),v.norm()};
    this->_u = u.normalize();
    this->_v = v.normalize();
}

bool Face::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    Plane plane = Plane(this->_point,this->_normal, this->_properties);

    if(!plane.intersect_with_ray(r,intersection))
        return false;
    
    Vector v = this->_point - intersection.get_point();

    if (geD(fabs(v.dot(this->_u)),this->_sizes[0]) ||  geD(fabs(v.dot(this->_v)),this->_sizes[1]))
        return false;
    else
        return true;
}

std::ostream& operator<<(std::ostream& os, const Face& f)
{
    os << f.to_string();
    return os;
}

std::string Face::to_string() const
{
    std::string sizes_str = "[" + std::to_string(_sizes[0]) + ", " + std::to_string(_sizes[1]) + "]";
    std::string str = "Face: " + _normal.to_string() + " " + _u.to_string() + " " + _v.to_string() + " " + sizes_str + " " + _point.to_string();
    return str;
}