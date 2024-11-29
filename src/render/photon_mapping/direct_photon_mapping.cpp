#include "render/photon_mapping/direct_photon_mapping.hpp"

DirectPhotonMapping::DirectPhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel):
    PhotonMapping(s, n_photons, max_photon_num_per_query, radius, std::move(kernel))
{}

Color DirectPhotonMapping::compute_ray_color(const Ray& r) const
{
    IntersectionObject min_int_obj;
    bool intersects = this->_scene.intersect_with_ray(r, min_int_obj);
    if(!intersects)
        return Color();
    
    if(min_int_obj.is_delta())
    {
        Ray new_ray;
        if(!min_int_obj.sample_ray(new_ray))
            return Color();
        
        return compute_ray_color(new_ray);
    } else
    {
        return this->density_estimate(min_int_obj);
    }
}

void DirectPhotonMapping::create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, size_t total_bounces, std::vector<Photon>& photons)
{
    if(num_bounces == total_bounces)
        return;

    IntersectionObject min_int_obj;
    bool intersects = this->_scene.intersect_with_ray(r, min_int_obj);

    if(!intersects)
        return;

    Ray new_ray;
    if(!min_int_obj.sample_ray(new_ray))
        return;

    Color new_flux = min_int_obj.eval_brdf(flux*M_PI, r.get_direction());
    
    if(!min_int_obj.is_delta())
    {
        Photon p = Photon(min_int_obj.get_int_point(), r.get_direction(), Color(new_flux));
        photons.push_back(p);
    }

    create_photon_trace_rec(new_ray, new_flux, num_bounces+1, total_bounces, photons);

    return;
}