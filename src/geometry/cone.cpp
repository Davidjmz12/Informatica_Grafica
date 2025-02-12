#include "geometry/cone.hpp"

#include <cmath>

Cone::Cone(Point center, Vector axe, double radius, std::shared_ptr<BRDF> brdf)
    : Geometry(brdf),
    _center(center),
    _axe(axe.normalize()),
    _height(axe.norm()),
    _radius(radius),
    _base(Disk(center, axe, radius, brdf))
{}

bool Cone::intersection_in_a_point(const Ray& r, double distance, IntersectionObject& intersection) const
{

    if(leD(distance,0))
        return false;

    // Calculate the intersection point on the cone surface
    Point point_int = r.evaluate(distance);

    double h = (point_int-this->_center).dot(this->_axe);
    if(ltD(h,0) || gtD(h,this->_height))
        return false;

    // Vector from the apex of the cone to the intersection point
    Vector vec = (point_int - (this->_center + this->_axe * this->_height)).normalize(); 

    // Project v onto the cone axis
    Vector v_parallel = this->_axe*vec.dot(this->_axe);
    Vector v_perpendicular = (vec - v_parallel).normalize();

    Vector normal = v_perpendicular-vec*v_perpendicular.dot(vec);
    

    // Normalize the normal vector
    normal = normal.normalize();

    intersection = IntersectionObject(distance, normal, point_int, *this->_brdf, r);
    return true;
}

bool Cone::intersect_with_cone(const Ray& r, IntersectionObject& intersection) const
{
    Vector o = r.get_point()-this->_center;
    double ov = o.dot(r.get_direction());
    double od = o.dot(this->_axe);
    double vd = r.get_direction().dot(this->_axe);
    double r2 = pow(this->_radius,2);
    double h2 = pow(this->_height,2);


    double c = o.dot(o) - od*od - r2 + 2*r2*od/this->_height - r2/h2*pow(od,2);
    double b = 2*ov - 2*od*vd + 2*r2*vd/this->_height - 2*r2/h2*od*vd;
    double a = 1 - vd*vd  - r2/h2*vd*vd;

    double delta = pow(b,2) - 4*a*c;

    if(leD(delta,0))
        return false;
    else if(eqD(delta,0))
    {
        if(eqD(a,0))
            return false;
        
        return intersection_in_a_point(r,-b/(2*a),intersection);
    } else
    {
        double s1 = (-b+sqrt(delta))/(2*a);
        double s2 = (-b-sqrt(delta))/(2*a);

        IntersectionObject i1, i2;
        if(intersection_in_a_point(r,s1,i1))
        {
            if(intersection_in_a_point(r,s2,i2))
            {
                intersection = i1 < i2 ? i1 : i2;
                return true;
            } else
            {
                intersection = i1;
                return true;
            }
        } else
        {
            if(intersection_in_a_point(r,s2,i2))
            {
                intersection = i2;
                return true;
            } else
            {
                return false;
            }
        }
    }
}

BoundingBox Cone::get_bounding_box() const
{
    Point vertex = this->_center + this->_axe*this->_height;
    double x_min = std::min(this->_center[0], vertex[0]) - this->_radius;
    double x_max = std::max(this->_center[0], vertex[0]) + this->_radius;
    double y_min = std::min(this->_center[1], vertex[1]) - this->_radius;
    double y_max = std::max(this->_center[1], vertex[1]) + this->_radius;
    double z_min = std::min(this->_center[2], vertex[2]) - this->_radius;
    double z_max = std::max(this->_center[2], vertex[2]) + this->_radius;
    return BoundingBox({x_min, x_max, y_min, y_max, z_min, z_max});

}

bool Cone::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    if(this->intersect_with_cone(r, intersection))
    {
        IntersectionObject base_int;
        if(this->_base.intersect_with_ray(r, base_int))
        {
            if(base_int < intersection)
                intersection = base_int;
        }
        return true;
    } else 
        return this->_base.intersect_with_ray(r, intersection);

}

std::string Cone::to_string() const
{
    std::stringstream ss;
    ss  << "Cone\n\tCenter: " << this->_center
        << "\n\tAxe: " << this->_axe
        << "\n\tHeight: " << this->_height
        << "\n\tRadius: " << this->_radius;

    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Cone& c)
{
    os << c.to_string();
    return os;
}