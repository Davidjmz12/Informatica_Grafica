#include "geometry/sphere.hpp"

Sphere::Sphere(Geometric center, double radius)
    : _center(center), _radius(radius)
{}
    
double Sphere::implicit(Geometric x) const
{
    return (x-this->_center).dot(x-this->_center) - pow(this->_radius,2);
}

bool Sphere::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    Geometric aux = r.point()-this->_center;

    double a = pow(r.direction().norm(),2);
    double b = 2*r.direction().dot(aux);
    double c = pow(aux.norm(),2) - pow(this->_radius,2);

    double disc = sqrt(pow(b,2)-4*a*c);

    // if (eqD(disc,0))
    // {
    //     Intersection();
    //     return true;
    // } else if (disc < 0)
    //     return false;
    // else {
    //     double t1 = (-b + disc) / 2*a;
    //     double t2 = (-b - disc) / 2*a;

    //     // Calcular el mínimo, actualizar interseccion
    // }

    return b > 0 || eqD(b,0);
}