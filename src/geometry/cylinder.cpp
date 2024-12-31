
#include "geometry/cylinder.hpp"

Cylinder::Cylinder(Point center, double radius, Vector axis, std::shared_ptr<Property> properties)
    : Geometry(properties), _center(center), _radius(radius), _axis(axis.normalize()), _height(axis.norm()),
      _top(Disk(center+axis,axis,radius,properties)), _bottom(Disk(center,axis,radius,properties))
{
    if(axis.norm() == 0)
        throw std::invalid_argument("The axis of the cylinder must be different from the zero vector");
    if(radius <= 0)
        throw std::invalid_argument("The radius of the cylinder must be positive");
}

BoundingBox Cylinder::get_bounding_box() const
{
    Point center = this->_center;
    Point last_center = center + _axis*_height;
    double x_min = std::min(center[0], last_center[0]);
    double x_max = std::max(center[0], last_center[0]);
    double y_min = std::min(center[1], last_center[1]);
    double y_max = std::max(center[1], last_center[1]);
    double z_min = std::min(center[2], last_center[2]);
    double z_max = std::max(center[2], last_center[2]);
    return BoundingBox({
        x_min-this->_radius, x_max+this->_radius,
        y_min-this->_radius, y_max+this->_radius,
        z_min-this->_radius, z_max+this->_radius
    });
}


bool Cylinder::intersection_in_a_point(const Ray& r, double distance, bool is_entering, IntersectionObject& intersection) const
{
    if(leD(distance,0))
        return false;

    Point point_int = r.evaluate(distance), projection;

    double h = (point_int-this->_center).dot(this->_axis);
    
    if(ltD(h,0) || gtD(h,this->_height))
        return false;

    Vector normal;
    projection= _center + _axis*(_axis).dot((point_int-_center)); 
    normal = (point_int-projection).normalize();
    intersection = IntersectionObject(distance, is_entering?normal:normal*(-1), point_int, *this->_properties, r, is_entering);
    return true;
}

bool Cylinder::intersect_with_ray_finite_cylinder(const Ray& r, IntersectionObject& intersection) const
{
    
    Vector aux_1,aux_2 ;
    aux_1 = r.get_point()-_center-_axis*(r.get_point()-_center).dot(_axis);
    aux_2 = r.get_direction()-_axis*(r.get_direction().dot(_axis));
    
    double a,b,c;
    a = aux_2.dot(aux_2);
    b = 2*aux_1.dot(aux_2);
    c = aux_1.dot(aux_1)-pow(_radius,2);

    double delta = pow(b,2)-4*a*c;

    if(leD(delta,0))
        return false;
    else if (eqD(delta,0))
    {
        if(eqD(a,0)) // no solution
            return false;

        return intersection_in_a_point(r,-b/(2*a),true,intersection);
    } else 
    {
        double s1 = (-b+sqrt(delta))/(2*a);
        double s2 = (-b-sqrt(delta))/(2*a);

        bool is_entering = s1*s2 > 0;
        
        IntersectionObject i1, i2;

        if(intersection_in_a_point(r,s1,is_entering,i1))
        {
            if(intersection_in_a_point(r,s2,is_entering,i2))
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
            if(intersection_in_a_point(r,s2,is_entering,i2))
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

bool Cylinder::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{

    // Check intersections with the infinite cylinder
    if(intersect_with_ray_finite_cylinder(r, intersection))
    {
        // Check intersections with the bases
        IntersectionObject aux_int;
        for (auto i: { _top, _bottom })
        {
            if(i.intersect_with_ray(r, aux_int))
            {
                intersection = aux_int < intersection ? aux_int : intersection;
            }
        }
        return true;
    } else
    {
        IntersectionObject aux_int;
        bool has_intersection = false;
        for (auto i: { _top, _bottom })
        {
            if(i.intersect_with_ray(r, aux_int))
            {
                intersection = aux_int < intersection ? aux_int : intersection;
                has_intersection = true;
            }
        }
        return has_intersection;
    }

}

std::string Cylinder::to_string() const
{
    std::stringstream ss;
    ss << "Cylinder: " << _center << " " << _radius << " " << _axis  << " " << _height;
    return ss.str();
}
