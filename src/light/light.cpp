#include <utility>

#include "light/light.hpp"

PunctualLight::PunctualLight(Point center, const SpectralColor& power)
    : _center(std::move(center)), _power(power)
{}

SpectralColor PunctualLight::light_contribution(const KDTree& tree, const IntersectionObject& intersection) const
{
    const Vector ray_dir = (this->_center-intersection.get_int_point());
    const double norm_ray_dir = ray_dir.norm();

    const auto r = Ray(intersection.get_int_point(),ray_dir);
    IntersectionObject shadow_intersect;
    bool shadow = tree.intersect_with_ray(r,shadow_intersect);
    shadow = shadow && shadow_intersect.get_distance() < norm_ray_dir;
    
    if (shadow)
        return {};
    
    return intersection.eval_brdf((this->_power/pow(ray_dir.norm(),2))*fabs(intersection.get_normal().dot(ray_dir.normalize())), ray_dir.normalize());
}


double Light::luminance_mean() const
{
    return this->_power.luminance_mean();
}

double Light::luminance_max() const
{
    return this->_power.luminance_max();
}