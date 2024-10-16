
#include "geometry/cylinder.hpp"

Cylinder::Cylinder(Point center, double radius, Vector axis, Property properties)
    : Geometry(properties), _center(center), _radius(radius), _axis(axis.normalize()), _height(axis.norm()),
      _top(Disk(center+axis,axis,radius,properties)), _bottom(Disk(center,axis,radius,properties))
{
    if(axis.norm() == 0)
        throw std::invalid_argument("The axis of the cylinder must be different from the zero vector");
    if(radius <= 0)
        throw std::invalid_argument("The radius of the cylinder must be positive");
}


Intersection Cylinder::intersection_in_a_point(const Ray& r, double distance) const
{
    Point point_int = r.evaluate(distance), projection;
    Vector normal;
    projection= _center + _axis*(_center-Point()).dot((point_int-_center)); 
    normal = (point_int-projection).normalize();
    return Intersection(distance,normal,point_int);
}

bool Cylinder::intersect_with_ray_infinite_cylinder(const Ray& r, Intersection& intersection) const
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
        if(eqD(a,0)) // no solution
            return false;
        
        intersection = intersection_in_a_point(r,-b/(2*a));
        return true;
    } else 
    {
        std::vector<Intersection> int_points;
        if(eqD(a,0)) // There is solution because b!=0
        {
            Intersection i1;
            i1 = intersection_in_a_point(r,-c/b);
            int_points.push_back(i1);
        }
        else
        {
            Intersection i1,i2;
            i1 = intersection_in_a_point(r,(-b+sqrt(delta))/(2*a));
            i2 = intersection_in_a_point(r,(-b-sqrt(delta))/(2*a));
            int_points.push_back(i1);
            int_points.push_back(i2);

        }

        intersection = Intersection::min(int_points);
        return true;
    }
}

bool Cylinder::intersect_with_ray_finite_cylinder(const Ray& r, Intersection& intersection) const
{
    if(!intersect_with_ray_infinite_cylinder(r, intersection))
        return false;
    
    double int_point_dot_axis = (intersection.get_point()-this->_center).dot(_axis);

    if( ltD(int_point_dot_axis, 0) || gtD(int_point_dot_axis, _height))
        return false;
    
    return true;
}

bool Cylinder::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    
    if(!intersect_with_ray_finite_cylinder(r, intersection)){
        Intersection int_min;
        bool int_min_exists = false;
        for(auto i: { _top, _bottom })
        {
            Intersection intersection_aux;
            if(i.intersect_with_ray(r, intersection_aux))
            {   
                int_min_exists=true;
                if(int_min.get_distance()>intersection_aux.get_distance())
                    int_min = intersection_aux;
            }
        }
        intersection = int_min;
        return int_min_exists;
    }

    return true;
}

std::string Cylinder::to_string() const
{
    std::stringstream ss;
    ss << "Cylinder: " << _center << " " << _radius << " " << _axis  << " " << _height;
    return ss.str();
}
