
#include "spatial_element/base.hpp"
#include "properties/brdf/all_brdf.hpp"


int main()
{
    double ref_cof_entry = 1.0;
    double ref_cof_exit = sqrt(2);

    Vector normal = Vector(0,0,1);
    Vector w_0 = Vector(-1,0,1).normalize();
    Point point_int = Point(0,0,0);

    DiffuseBRDF diffuse = DiffuseBRDF();

    Ray sampled_ray;

    for(int i=0; i<10; i++)
    {
        diffuse.sample_ray(w_0, point_int, normal, ref_cof_entry, sampled_ray, tr ue);
        std::cout << sampled_ray.get_direction().to_string() << std::endl;
    }

}

