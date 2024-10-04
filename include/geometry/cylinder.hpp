#include "geometry/geometry.hpp"

class Cylinder: public Geometry
{
private:
    Geometric _center;
    float _radius;
    Geometric _axis;
    float _height;

    bool Cylinder::intersect_with_ray_infinite_cylinder(const Ray& r, Intersection& intersection) const;

    Intersection intersection_in_a_point(const Ray& r, float distance) const;

public:
    Cylinder(Geometric center, float radius, Geometric axis);

    float implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;


};