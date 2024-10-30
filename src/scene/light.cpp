#include "scene/light.hpp"

Light::Light(Point center, SpectralColor power)
    : _center(center), _power(power)
{}

SpectralColor Light::light_contribution(std::vector<Geometry*> geometries, const Intersection& intersection) const
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

    SpectralColor light = (this->_power/pow(norm_ray_dir,2));

    return light;

}