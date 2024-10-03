
#include "geometry/cylinder.hpp"

Cylinder::Cylinder(Geometric center, float radius, Geometric axis)
    : _center(center), _radius(radius), _axis(axis.normalize()), _height(axis.norm())
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

Intersection Cylinder::intersection_in_a_point(const Ray& r, float distance) 
{
    Geometric point_int = r.evaluate(distance);
    Geometric normal,projection;
    projection= _center + _axis*_center.dot(point_int-_center); 
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
        intersection = intersection_in_a_point(r,-b/(2*a));
        return true;
    } else 
    {

    }
}

bool Cylinder::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    if(!intersect_with_ray_infinite_cylinder(r, intersection))
        return false;
    
    if(intersection.point().dot(_axis) < 0 || intersection.point().dot(_axis) > _height)
        return false;
    
    return true;
}