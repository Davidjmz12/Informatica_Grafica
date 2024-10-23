#include "light.hpp"

Light::Light(Point center, Color power)
    : _center(center), _power(power)
{}

bool Light::meets_light(std::vector<Geometry*> geometries, const Intersection& intersection) const
{
    Vector ray_dir = (this->_center-intersection.get_point());
    double norm_ray_dir = ray_dir.norm();
    Ray r = Ray(intersection.get_point(),ray_dir);
    Intersection shadow_intersect;
    for(Geometry* g: geometries)
    {
        if(g->intersect_with_ray(r,shadow_intersect) && ltD(shadow_intersect.get_distance(), norm_ray_dir))
            return false;
    }

    double z = fabs(intersection.get_normal().dot(ray_dir.normalize()));
    Color light_color = (this->_power/pow(norm_ray_dir,2))*
                        (intersection.get_properties().get_BRDF()->eval(
                                    intersection.get_point(), 
                                    ray_dir.normalize(),
                                    intersection.)*z);

    return true;

}