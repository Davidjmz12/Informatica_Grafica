#include "geometry/geometry.hpp"
#include "geometry/disk.hpp"

class Cylinder: public Geometry
{
private:
    Point _center;
    double _radius;
    Vector _axis;
    double _height;
    Disk _top, _bottom;

    bool intersect_with_ray_infinite_cylinder(const Ray& r, Intersection& intersection) const;

    bool intersect_with_ray_finite_cylinder(const Ray& r, Intersection& intersection) const;

    Intersection intersection_in_a_point(const Ray& r, double distance) const;

public:
    Cylinder(Point center, double radius, Vector axis);

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;

    std::string to_string() const;
};