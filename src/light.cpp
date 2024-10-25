#include "light.hpp"

Light::Light(Point center, SpectralColor power)
    : _center(center), _power(power)
{}

SpectralColor Light::meets_light(std::vector<Geometry*> geometries, const Intersection& intersection) const
{
    Vector ray_dir = (this->_center-intersection.get_point());
    double norm_ray_dir = ray_dir.norm();
    Ray r = Ray(intersection.get_point(),ray_dir);
    Intersection shadow_intersect;
    for(Geometry* g: geometries)
    {
        if(g->intersect_with_ray(r,shadow_intersect) && ltD(shadow_intersect.get_distance(),norm_ray_dir)
            && ltD(0, shadow_intersect.get_distance()))
            return SpectralColor();
    }

    double z = fabs(intersection.get_normal().dot(ray_dir.normalize()));
    SpectralColor c1 = (this->_power/pow(norm_ray_dir,2));
    SpectralColor c2 = (intersection.get_properties().get_BRDF()->eval(
                                    intersection.get_point(), 
                                    ray_dir.normalize(),
                                    intersection.get_origin()));

    SpectralColor light_color = c1*c2*z;

    return light_color;

}