#include "geometry/cone.hpp"

/**
 * @brief Function that solves a equation of second degree
 * @param a The coefficient of x**2
 * @param b The coefficient of x
 * @param c The independent term
 * @return A vector of solutions ordered form lower to greater
 */
std::vector<double> solve_equation_second_degree(double a, double b, double c)
{
    std::vector<double> solutions;
    // Case a=0: Equation of one degree.
    if (eqD(a,0))
    {
        if (eqD(b,0))
            return solutions;
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
        return solutions;

}

Cone::Cone(Point vertex, Vector axe, double height, double radius, Property properties)
    : Geometry(properties),
    _vertex(vertex),
    _axe(axe),
    _height(height),
    _radius(radius),
    _base(Disk(vertex + axe.normalize()*height, axe.normalize(), radius, properties))
{
    // Translate the vertex of the cone to the origin
    LinearMap t = LinearMap::translation(Vector(vertex)*-1);

    // Rotate the cone to put the axe on the z-axe
    Vector e3 = Vector(0,0,1);
    LinearMap r = LinearMap::identity();
    if (axe.linearly_dependent(e3))
    {
        if (!(axe.normalize() == e3))
            r = LinearMap::rotation(Vector(1,0,0),M_PI);
    }
    else
        r = LinearMap::rotation(axe.cross(e3),acos(axe.dot(e3)/axe.norm()));
    
    double scaler[3] = {1/radius, 1/radius, 1/height};
    LinearMap s = LinearMap::scale(scaler);

    this->_max_distance = height;
    
    // Compose tranformations
    this->_centering = s*r*t;
    this->_centering_inverse = this->_centering.inverse();
}

bool Cone::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    // Information of the ray centralized in vertex (0,0,0) and axe (0,0,1)
    Vector direction = Vector(this->_centering*new Vector(r.get_direction()));
    Point origin = Point(this->_centering*new Point(r.get_point()));

    // Compute the coefficients of the equation of second degree at**2 + bt + c = 0
    double a = pow(direction[0],2) + pow(direction[1],2) - pow(direction[2],2);
    double b = 2*(origin[0]*direction[0] + origin[1]*direction[1] - origin[2]*direction[2]);
    double c = pow(origin[0],2) + pow(origin[1],2) - pow(origin[2],2);
    
    // Compute the solution
    std::vector<double> solution = solve_equation_second_degree(a,b,c);
    if (solution.size() == 0)
        return false;

    // Check if we have positive solution
    double distance = solution[solution.size()-1]; // Minimum
    if (!gtD(distance,0))
        return false;

    // Compute the normal vector
    Point intersection_point = origin + direction*distance;

    // Check if intersects in a finite cone
    if (gtD(intersection_point[2],1) ||
        ltD(intersection_point[2],0))
        return false;

    // Compute the normal vector
    Vector normal_vector = Vector();
    if (!(Point() == intersection_point))
    {
        Vector v1 = Vector(intersection_point);
        Vector v2 = Vector(0,0,1).cross(Vector( intersection_point[0],
                                                intersection_point[1],
                                                0));
        normal_vector = v1.cross(v2);
    }
    else
        normal_vector = Vector(0,0,1);

    // Create the intersection object
    normal_vector = Vector(this->_centering_inverse*(new Vector(normal_vector)));
    intersection_point = Point(this->_centering_inverse*(new Point(intersection_point)));

    intersection = Intersection(distance,normal_vector,intersection_point,this->_properties,r.get_direction());

    return true;
}

std::string Cone::to_string() const
{
    std::stringstream ss;
    ss  << "Cone\n\tVertex: " << this->_vertex
        << "\n\tAxe: " << this->_axe
        << "\n\tHeight: " << this->_height
        << "\n\tRadius: " << this->_radius;

    return ss.str();
}