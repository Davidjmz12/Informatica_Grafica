#include "geometry/ellipsoid.hpp"

std::vector<double> solve_equation_second_degree(double a, double b, double c)
{
    std::vector<double> solutions;
    // Case a=0: Equation of one degree.
    if (eqD(a,0))
    {
        if (eqD(b,0))
        {
            return solutions;
        }
        else
        {
            solutions.push_back(-c/b);
            return solutions;
        }
    }



    // Make a > 0 
    if (a < 0)
    {
        a = -a;
        b = -b;
        c = -c;
    }

    // Compute the solution
    double disc = sqrt(pow(b,2) - 4*a*c);
    if (eqD(disc,0))
    {
        solutions.push_back(-b/(2*a));
        return solutions;
    } else if (disc > 0)
    {
        solutions.push_back((-b + disc)/(2*a));
        solutions.push_back((-b - disc)/(2*a));
        return solutions;
    } else 
    {
        return solutions;
    }

}

Ellipsoid::Ellipsoid(double a, double b, double c, Point center, Property properties)
    : Geometry(properties), _a(a), _b(b), _c(c), _center(center)
{
    if (eqD(a,0) || eqD(b,0) || eqD(c,0))
        throw std::invalid_argument("Factors cannot be zero.");
}

bool Ellipsoid::intersect_with_ray(const Ray& r, Intersection& intersection) const
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
    bool existSolution = solution.size() > 0;

    // If there is no solution, return false
    if(!existSolution)
        return false;

    double distance = 0;
    for(double d : solution)
        if (gtD(d,0))
            distance = d;

    // If the ray is in the ellipsoid or behind it, return false
    if (distance == 0)
        return false;


    Point point_int = r.evaluate(distance);
    intersection = Intersection(distance, this->normal(point_int), point_int, this->_properties, r.get_direction());

    return existSolution;    
}

Vector Ellipsoid::normal(Point p) const
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