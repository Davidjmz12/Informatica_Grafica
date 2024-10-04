#include "ellipsoid.hpp"

std::tuple<bool,float> solve_equation_second_degree(float a, float b, float c)
{
    // Case a=0: Equation of one degree.
    if (eqFloat(a,0))
        if (eqFloat(b,0))
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
    float disc = sqrt(pow(b,2) - 4*a*c);
    if (eqFloat(disc,0))
        return std::make_tuple(true,-b/(2*a));
    else if (disc > 0)
        return std::make_tuple(true,(-b - disc)/(2*a));
    else
        return std::make_tuple(false,0.0);
}

Ellipsoid::Ellipsoid(float a, float b, float c, Geometric center)
    : _a(a), _b(b), _c(c), _center(center)
{
    if (eqFloat(a,0) || eqFloat(b,0) || eqFloat(c,0))
        throw std::invalid_argument("Factors cannot be zero.");
}

bool Ellipsoid::intersect_with_ray(Ray r, Intersection& intersection) const
{
    //Compute the necessary data
    Geometric direction = r.direction();
    float dx = direction[0], dy = direction[1], dz = direction[2];
    float A = 1/(pow(this->_a,2)), B = 1/(pow(this->_b,2)), C = 1/(pow(this->_c,2));
    float ox = this->_center[0], oy = this->_center[1], oz = this->_center[2];

    //Compute the coefficients
    float a = A*pow(dx,2) + B*pow(dy,2) + C*pow(dz,2);
    float b = 2*(A*dx*ox + B*dy*oy + C*dz*oz);
    float c = A*pow(ox,2) + B*pow(oy,2) + C*pow(oz,2) - 1;

    // Check if exists solution
    if (eqFloat(a,0) && eqFloat(b,0))
        return false;
    else
    {
        //Calculate the solution
        std::tuple solution = solve_equation_second_degree(a,b,c);
        bool existSolution;
        float numericSolution;
        std::tie(existSolution,numericSolution) = solution;

        //Construct intersection
        if (existSolution)
        {
            Geometric point = r.evaluate_point(numericSolution);
            intersection = Intersection(numericSolution, this->normal(point), point);
        }

        return existSolution;
    }
}

Geometric Ellipsoid::normal(Geometric p) const
{
    //Check if the point belongs to the ellipsoid
    if (!this->is_in_ellipsoid(p))
        throw std::runtime_error("The given point is not in the ellipsoid.");

    //Compute the normal vector
    return Geometric::vector(   p[0]/pow(this->_a,2),
                                p[1]/pow(this->_b,2),
                                p[2]/pow(this->_c,2)).normalize();
}

bool Ellipsoid::is_in_ellipsoid(Geometric p) const
{
    return  eqFloat(pow(p[0]-this->_center[0],2)/pow(this->_a,2) +
                    pow(p[1]-this->_center[1],2)/pow(this->_b,2) + 
                    pow(p[2]-this->_center[2],2)/pow(this->_c,2),0);
}

