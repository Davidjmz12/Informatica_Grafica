#include "geometry/face.hpp"

Face::Face(Vector normal, Vector u, Vector v, Point point, std::shared_ptr<BRDF> brdf)
    :  Geometry(brdf), _normal(normal), _point(point)
{
    if (neqD(normal.dot(u),0) || neqD(normal.dot(v),0))
        throw std::invalid_argument("The vectors u and v must be perpendicular to the normal vector.");
    if (!normal.is_base(u,v))
        throw std::invalid_argument("The vectors u, v and the norm must be a R^3 base.");
    
    this->_sizes = {u.norm(),v.norm()};
    this->_u = u.normalize();
    this->_v = v.normalize();
}


BoundingBox Face::get_bounding_box() const
{
    std::vector<Point> corners;
    for(size_t i:{0,1})
        for(size_t j:{0,1})
            corners.push_back(this->_point + this->_u*i*this->_sizes[0] + this->_v*j*this->_sizes[1]);
    
    return BoundingBox::get_BB_by_corners(corners);
}

std::pair<double, double> Face::get_u_v_coordinates(const Point& p) const
{
    Base b = Base(this->_point, this->_normal, this->_u*this->_sizes[0], this->_v*this->_sizes[1]);
    Vector vec = Vector(b.coord_from_canonical(&p));
    return {vec[1],vec[2]};
}

bool Face::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    Plane plane = Plane(this->_point,this->_normal, this->_brdf);

    if(!plane.intersect_with_ray(r,intersection))
        return false;
    
    Vector vec = this->_point - intersection.get_int_point();

    if (geD(fabs(vec.dot(this->_u)),this->_sizes[0]) ||  geD(fabs(vec.dot(this->_v)),this->_sizes[1]))
        return false;
    
    intersection.set_u_v(this->get_u_v_coordinates(intersection.get_int_point()));

    return true;
}

Ray Face::sample_ray() const
{
    double u = randomD(0,1);
    double v = randomD(0,1);

    Point point = this->_point + this->_u*u*this->_sizes[0] + this->_v*v*this->_sizes[1];

    Vector vec = Base::sample_hemisphere(this->_normal, point);

    return Ray(point,vec);
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

