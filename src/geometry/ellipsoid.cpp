#include <utility>

#include "geometry/ellipsoid.hpp"

BoundingBox Ellipsoid::get_bounding_box() const
{
    return BoundingBox(
        {
            this->_center[0]-this->_a, this->_center[0]+this->_a,
            this->_center[1]-this->_b, this->_center[1]+this->_b,
            this->_center[2]-this->_c, this->_center[2]+this->_c
        }
    );
}

Ellipsoid::Ellipsoid(const double a, const double b, const double c, Point center, std::shared_ptr<Property> properties)
    : Geometry(std::move(properties)), _a(a), _b(b), _c(c), _center(std::move(center))
{
    if (eqD(a,0) || eqD(b,0) || eqD(c,0))
        throw std::invalid_argument("Factors cannot be zero.");
}

bool Ellipsoid::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    Vector dir_ray = r.get_direction();
    Point point_centered = Point(r.get_point()-this->_center);

    double c = pow(point_centered[0]/this->_a,2) + 
               pow(point_centered[1]/this->_b,2) + 
               pow(point_centered[2]/this->_c,2) - 1;

    double b =  2*dir_ray[0]*point_centered[0]/pow(this->_a,2) +
                2*dir_ray[1]*point_centered[1]/pow(this->_b,2) +
                2*dir_ray[2]*point_centered[2]/pow(this->_c,2); 

    double a =  pow(dir_ray[0]/this->_a,2) +
                pow(dir_ray[1]/this->_b,2) +
                pow(dir_ray[2]/this->_c,2);


    //Calculate the solution
    std::vector<double> solution = solve_equation_second_degree(a,b,c);
    bool existSolution = !solution.empty();

    // If there is no solution, return false
    if(!existSolution)
        return false;

    double distance = 0;
    for(const double d : solution)
        if (gtD(d,0))
            distance = d;

    // If the ray is in the ellipsoid or behind it, return false
    if (distance == 0)
        return false;


    const Point point_int = r.evaluate(distance);

    const Vector p_inside = (r.get_point()-this->_center);
    bool is_entering = true;
    if (leD(pow(p_inside[0],2)/pow(this->_a,2) + pow(p_inside[1],2)/pow(this->_b,2) + pow(p_inside[2],2)/pow(this->_c,2), 1))
        is_entering = false;

    Vector normal = is_entering ? this->normal(point_int) : this->normal(point_int)*(-1);
    intersection = IntersectionObject(distance, normal, point_int, this->_properties, r, is_entering);

    return existSolution;    
}

Vector Ellipsoid::normal(const Point& p) const
{
    //Compute the normal vector
    return Vector(  (p[0]-this->_center[0])/pow(this->_a,2),
                    (p[1]-this->_center[1])/pow(this->_b,2),
                    (p[2]-this->_center[2])/pow(this->_c,2)).normalize();
}

std::ostream& operator<<(std::ostream& os, const Ellipsoid& e)
{
    os << e.to_string();
    return os;
}

std::string Ellipsoid::to_string() const
{
    return "Ellipsoid: " + this->_center.to_string() + " ; " + std::to_string(this->_a) + " ; " + std::to_string(this->_b) + " ; " + std::to_string(this->_c);
}