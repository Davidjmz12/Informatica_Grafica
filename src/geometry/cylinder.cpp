
#include "geometry/cylinder.hpp"

Cylinder::Cylinder(Geometric center, float radius, Geometric axis)
    : _center(center), _radius(radius), _axis(axis.normalize()), _height(axis.norm()),
      _top(Disk(center+axis,axis,radius)), _bottom(Disk(center,axis,radius))
{
    if(axis.norm() == 0)
        throw std::invalid_argument("The axis of the cylinder must be different from the zero vector");
    if(radius <= 0)
        throw std::invalid_argument("The radius of the cylinder must be positive");
}

float Cylinder::implicit(Geometric x) const
{
    return (x-_center).dot(x-_center)-pow(_radius,2) - pow((x-_center).dot(_axis),2);
}

Intersection Cylinder::intersection_in_a_point(const Ray& r, float distance) const
{
    Geometric point_int = r.evaluate(distance);
    Geometric normal,projection;
    projection= _center + _axis*(_center-Geometric::point0()).dot(point_int-_center); 
    normal = (point_int-projection).normalize();
    return Intersection(distance,normal,point_int);
}

bool Cylinder::intersect_with_ray_infinite_cylinder(const Ray& r, Intersection& intersection) const
{
    
    Geometric aux_1,aux_2 ;
    aux_1 = r.point()-_center-_axis*(r.point()-_center).dot(_axis);
    aux_2 = r.direction()-_axis*(r.direction().dot(_axis));
    
    float a,b,c;
    a = aux_2.dot(aux_2);
    b = 2*aux_1.dot(aux_2);
    c = aux_1.dot(aux_1)-pow(_radius,2);

    float delta = pow(b,2)-4*a*c;

    if(delta<0)
        return false;
    else if (delta==0)
    {
        if(eqFloat(a,0)) // no solution
            return false;
        
        intersection = intersection_in_a_point(r,-b/(2*a));
        return true;
    } else 
    {
        std::vector<Intersection> int_points;
        if(eqFloat(a,0)) // There is solution because b!=0
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
    
    float int_point_dot_axis = (intersection.point()-Geometric::point0()).dot(_axis);

    if( ltFloat(int_point_dot_axis, 0) || gtFloat(int_point_dot_axis, _height))
        return false;
    
    return true;
}

bool Cylinder::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    
    if(!intersect_with_ray_finite_cylinder(r, intersection)){
        std::vector<Intersection> int_bases;
        for(auto i: { _top, _bottom })
        {
            Intersection intersection_aux;
            if(i.intersect_with_ray(r, intersection_aux))
            {
                int_bases.push_back(intersection_aux);
            }
        }
        
        if(int_bases.size() == 0)
            return false;
        else{
            intersection = Intersection::min(int_bases);
            return true;
        }    
    }

    return true;
}