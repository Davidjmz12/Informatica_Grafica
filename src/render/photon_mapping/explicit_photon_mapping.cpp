#include "render/photon_mapping/explicit_photon_mapping.hpp"

ExplicitPhotonMapping::ExplicitPhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel):
    PhotonMapping(s, n_photons, max_photon_num_per_query, radius, std::move(kernel))
{}

Color ExplicitPhotonMapping::compute_ray_color(const Ray& r) const
{
    IntersectionObject min_int_obj;
    bool intersects = this->_scene.intersect_with_ray(r, min_int_obj);
    if(!intersects)
        return Color();
    
    Ray new_ray;
    BRDFType sampled = min_int_obj.sample_ray(new_ray);

    if(sampled == BRDFType::ABSORPTION)
        return Color();

    if(BRDF::is_delta(sampled))
    {
        return compute_ray_color(new_ray);
    } else
    {
        Color density_estimate = this->density_estimate(min_int_obj, sampled);
        Color direct_light = this->calculate_punctual_light_contribution(min_int_obj, sampled);
        return density_estimate + direct_light;
    }
}

void ExplicitPhotonMapping::create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, size_t total_bounces, std::vector<Photon>& photons)
{
    if(num_bounces == total_bounces)
        return;

    IntersectionObject min_int_obj;
    bool intersects = this->_scene.intersect_with_ray(r, min_int_obj);

    if(!intersects)
        return;

    Ray new_ray;
    BRDFType sampled = min_int_obj.sample_ray(new_ray);
    if(sampled == BRDFType::ABSORPTION)
        return;

    Color new_flux = min_int_obj.eval_brdf(flux*M_PI, r.get_direction(), sampled);
    

    // If it is not direct light and it is not a delta, store the photon
    if(num_bounces > 0 && !BRDF::is_delta(sampled))
    {
        Photon p = Photon(min_int_obj.get_int_point(), r.get_direction(), Color(new_flux));
        photons.push_back(p);
    }

    create_photon_trace_rec(new_ray, new_flux, num_bounces+1, total_bounces, photons);

    return;
}