
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


IntersectionObject Cylinder::intersection_in_a_point(const Ray& r, double distance) const
{
    if(eqD(distance,0))
        return IntersectionObject();
    Point point_int = r.evaluate(distance), projection;
    Vector normal;
    projection= _center + _axis*(_center-Point()).dot((point_int-_center)); 
    normal = (point_int-projection).normalize();
    return IntersectionObject(distance, normal, point_int, *this->_properties, r);
}

bool Cylinder::intersect_with_ray_infinite_cylinder(const Ray& r, IntersectionObject& intersection) const
{
    
    Vector aux_1,aux_2 ;
    aux_1 = r.get_point()-_center-_axis*(r.get_point()-_center).dot(_axis);
    aux_2 = r.get_direction()-_axis*(r.get_direction().dot(_axis));
    
    double a,b,c;
    a = aux_2.dot(aux_2);
    b = 2*aux_1.dot(aux_2);
    c = aux_1.dot(aux_1)-pow(_radius,2);

    double delta = pow(b,2)-4*a*c;

    if(delta<0)
        return false;
    else if (delta==0)
    {
        if(eqD(a,0) || eqD(b,0)) // no solution
            return false;
        
        intersection = intersection_in_a_point(r,-b/(2*a));
        return true;
    } else 
    {
        std::vector<IntersectionObject> int_points;
        int_points.push_back(intersection_in_a_point(r,(-b+sqrt(delta))/(2*a)));
        int_points.push_back(intersection_in_a_point(r,(-b-sqrt(delta))/(2*a)));

        if (int_points[0] < int_points[1])
            intersection = int_points[0];
        else
            intersection = int_points[1];

        return true;
    }
}

bool Cylinder::intersect_with_ray_finite_cylinder(const Ray& r, IntersectionObject& intersection) const
{
    if(!intersect_with_ray_infinite_cylinder(r, intersection))
        return false;
    
    double int_point_dot_axis = (intersection.get_int_point()-this->_center).dot(_axis);

    if( ltD(int_point_dot_axis, 0) || gtD(int_point_dot_axis, _height))
        return false;
    
    return true;
}

bool Cylinder::intersect_with_base(const Ray& r, IntersectionObject& intersection) const
{
    bool int_min_exists = false;
    IntersectionObject aux_int;
    for (auto i: { _top, _bottom })
    {
        if(i.intersect_with_ray(r, aux_int))
        {
            int_min_exists = true;
            if(intersection>aux_int)
                intersection = aux_int;
        }
    }
    return int_min_exists;
}

bool Cylinder::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    IntersectionObject intersection_base, intersection_cylinder;
    bool intersection_with_base = false, intersection_with_cylinder = false;

    intersection_with_base = intersect_with_base(r, intersection_base);
    intersection_with_cylinder = intersect_with_ray_finite_cylinder(r, intersection_cylinder);

    intersection = (intersection_base<intersection_cylinder)?intersection_base:intersection_cylinder;

    Vector a = r.get_point()-_center;
    Vector b = a - _axis*a.dot(_axis);
    bool inside_bases_cylinder = geD(a.dot(_axis), 0) && leD(a.dot(_axis), _height);
    bool inside_center = leD(b.norm(), _radius);
    bool is_entering = !(inside_bases_cylinder && inside_center);
    if(!is_entering)
    {
        intersection.inverse_normal();
        intersection.set_is_entering(false);
    }


    return intersection_with_base || intersection_with_cylinder;
}

std::string Cylinder::to_string() const
{
    std::stringstream ss;
    ss << "Cylinder: " << _center << " " << _radius << " " << _axis  << " " << _height;
    return ss.str();
}
