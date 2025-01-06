#include <utility>

#include "light/punctual_light.hpp"

PunctualLight::PunctualLight(Point center, const Color& power)
    : _center(std::move(center)), _power(power)
{}

Ray PunctualLight::sample_ray() const
{
    const double theta = acos(2*randomD(0,1)-1);
    const double phi = 2*M_PI*randomD(0,1);

    const auto v = Vector(cos(theta)*cos(phi), cos(theta)*sin(phi),sin(theta));
    return Ray(this->_center, v); 
}

Color PunctualLight::light_contribution(const KDTree& tree, const IntersectionObject& intersection,  BRDFType type) const
{
    const Vector ray_dir = (this->_center-intersection.get_int_point());
    const double norm_ray_dir = ray_dir.norm();

    const auto r = Ray(intersection.get_int_point(),ray_dir);
    IntersectionObject shadow_intersect;
    bool shadow = tree.intersect_with_ray(r,shadow_intersect);
    shadow = shadow && shadow_intersect.get_distance() < norm_ray_dir;
    
    if (shadow)
        return {};
    
    return intersection.eval_brdf((this->_power/pow(ray_dir.norm(),2))*fabs(intersection.get_normal().dot(ray_dir.normalize())), 
        ray_dir.normalize(), type);
}


double PunctualLight::luminance_mean() const
{
    return this->_power.luminance_mean();
}

double PunctualLight::luminance_max() const
{
    return this->_power.luminance_max();
}