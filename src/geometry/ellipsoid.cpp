#include "geometry/ellipsoid.hpp"

std::tuple<bool,double> solve_equation_second_degree(double a, double b, double c)
{
    // Case a=0: Equation of one degree.
    if (eqD(a,0))
        if (eqD(b,0))
            throw std::invalid_argument("Parameters a and b cannot be 0 at the same time");
        else
            return std::make_tuple(true, -c/b);

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
        return std::make_tuple(true,-b/(2*a));
    else if (disc > 0)
        return std::make_tuple(true,(-b - disc)/(2*a));
    else
        return std::make_tuple(false,0.0);
}

Ellipsoid::Ellipsoid(double a, double b, double c, Point center)
    : _a(a), _b(b), _c(c), _center(center)
{
    if (eqD(a,0) || eqD(b,0) || eqD(c,0))
        throw std::invalid_argument("Factors cannot be zero.");
}

bool Ellipsoid::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    //Traslation to the canonical center of the ellipsoid
    Ray ray = Ray(r.get_point()-(this->_center-Point()),r.get_direction());

    //Compute the necessary data
    Vector direction = ray.get_direction();
    double dx = direction[0], dy = direction[1], dz = direction[2];
    double A = 1/(pow(this->_a,2)), B = 1/(pow(this->_b,2)), C = 1/(pow(this->_c,2));
    Point point = ray.get_point();
    double ox = point[0], oy = point[1], oz = point[2];

    //Compute the coefficients
    double a = A*pow(dx,2) + B*pow(dy,2) + C*pow(dz,2);
    double b = 2*(A*dx*ox + B*dy*oy + C*dz*oz);
    double c = A*pow(ox,2) + B*pow(oy,2) + C*pow(oz,2) - 1;

    // Check if exists solution
    if (eqD(a,0) && eqD(b,0))
        return false;
    else
    {
        //Calculate the solution
        std::tuple solution = solve_equation_second_degree(a,b,c);
        bool existSolution;
        double numericSolution;
        std::tie(existSolution,numericSolution) = solution;

        //Construct intersection
        if (existSolution)
        {
            Point point = ray.evaluate(numericSolution);
            point = point + (this->_center - Point());
            intersection = Intersection(numericSolution, this->normal(point), point);
        }

        return existSolution;
    }
}

Vector Ellipsoid::normal(Point p) const
{
    //Check if the point belongs to the ellipsoid
    if (!this->is_in_ellipsoid(p))
        throw std::runtime_error("The given point is not in the ellipsoid.");

    //Compute the normal vector
    return Vector(  (p[0]-this->_center[0])/pow(this->_a,2),
                    (p[1]-this->_center[1])/pow(this->_b,2),
                    (p[2]-this->_center[2])/pow(this->_c,2)).normalize();
}

bool Ellipsoid::is_in_ellipsoid(Point p) const
{
    return  eqD(pow(p[0]-this->_center[0],2)/pow(this->_a,2) +
                    pow(p[1]-this->_center[1],2)/pow(this->_b,2) + 
                    pow(p[2]-this->_center[2],2)/pow(this->_c,2),1);
}

