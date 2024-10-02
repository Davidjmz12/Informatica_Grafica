#include "sphere.hpp"

Sphere::Sphere(Geometric center, float radius)
    : _center(center), _radius(radius)
{}
    
float Sphere::implicit(Geometric x) const
{
    return (x-this->_center).dot(x-this->_center) - pow(this->_radius,2);
}

bool Sphere::intersect_with_ray(Ray r, Intersection& intersection) const
{
    Geometric aux = r.point()-this->_center;

    float a = pow(r.direction().norm(),2);
    float b = 2*r.direction().dot(aux);
    float c = pow(aux.norm(),2) - pow(this->_radius,2);

    float disc = sqrt(pow(b,2)-4*a*c);

    // if (eqFloat(disc,0))
    // {
    //     Intersection();
    //     return true;
    // } else if (disc < 0)
    //     return false;
    // else {
    //     float t1 = (-b + disc) / 2*a;
    //     float t2 = (-b - disc) / 2*a;

    //     // Calcular el mínimo, actualizar interseccion
    // }

    return b > 0 || eqFloat(b,0);
}