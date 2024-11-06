
#include "spatial_element/base.hpp"

int main()
{
    double theta_entry = M_PI;
    double ref_cof_entry = 1.0;
    double ref_cof_exit = 0.8;

    Vector normal = Vector(0,0,1);
    Vector dir_int = Vector(1,0,-1);
    Point point_int = Point(0,0,0);

    double theta_exit = asin(sin(theta_entry)/ref_cof_entry*ref_cof_exit);
    
    Vector orth = (dir_int-normal*dir_int.dot(normal)).normalize();

    Base base = Base(point_int, orth, orth.cross(normal*(-1)) , normal*(-1));
    
    Vector final_dir = Vector(base.coord_from_canonical(new Vector(sin(theta_exit),0,cos(theta_exit))));

    std::cout << (final_dir);
}

