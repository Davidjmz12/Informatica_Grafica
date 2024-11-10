#include "light/light.hpp"

PunctualLight::PunctualLight(Point center, SpectralColor power)
    : _center(center), _power(power)
{}

SpectralColor PunctualLight::light_contribution(std::vector<Geometry*> geometries, const IntersectionObject& intersection) const
{
    Vector ray_dir = (this->_center-intersection.get_int_point());
    double norm_ray_dir = ray_dir.norm();

    Ray r = Ray(intersection.get_int_point(),ray_dir);
    IntersectionObject shadow_intersect;
    bool shadow = false;
    for(Geometry* g: geometries)
    {
        if(g->intersect_with_ray(r,shadow_intersect) && ltD(shadow_intersect.get_distance(),norm_ray_dir)
            && ltD(0, shadow_intersect.get_distance()))
            shadow = true;
    }
    
    if (shadow)
        return SpectralColor();
    
    return intersection.eval_brdf((this->_power/pow(ray_dir.norm(),2))*fabs(intersection.get_normal().dot(ray_dir.normalize())), ray_dir.normalize());
}