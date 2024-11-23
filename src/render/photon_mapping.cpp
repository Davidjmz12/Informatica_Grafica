#include <cmath>

#include "render/photon_mapping.hpp"


Color PhotonMapping::density_estimate(const IntersectionObject& obj) const
{
    Color sum;
    for(const Photon* p : this->_photon_map.nearest_neighbors(obj.get_int_point(), this->_max_photon_num_per_query, this->_radius))
    {
        double distance = (p->get_position() - obj.get_int_point()).norm();
        sum = sum + obj.eval_brdf(p->get_flux()*this->_kernel->eval(distance, this->_radius), p->get_vector());
    }

    return sum;
}

Color PhotonMapping::compute_ray_color(const Ray& r) const
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

void PhotonMapping::create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, std::vector<Photon>& photons)
{
    if(num_bounces == 0)
        return;

    IntersectionObject min_int_obj;
    bool intersects = this->_scene.intersect_with_ray(r, min_int_obj);

    if(!intersects)
        return;

    Ray new_ray;
    if(!min_int_obj.sample_ray(new_ray))
        return;

    Color new_flux = min_int_obj.eval_brdf(flux*M_PI, r.get_direction());
    
    if(min_int_obj.is_delta())
    {
        create_photon_trace_rec(new_ray, new_flux, num_bounces-1, photons);
        return;
    }

    Photon p = Photon(min_int_obj.get_int_point(), r.get_direction(), Color(new_flux));
    photons.push_back(p);

    create_photon_trace_rec(new_ray, new_flux, num_bounces-1, photons);

    return;
}

void PhotonMapping::create_photon_trace(const PunctualLight& light, double weight, std::vector<Photon>& photons)
{
    Ray r = light.sample_random_unitary_ray();

    size_t num_bounces = this->_gc->get_number_of_bounces();

    create_photon_trace_rec(r, Color(4*M_PI*light.luminance_max()/weight), num_bounces, photons);
}

PhotonMap PhotonMapping::create_photon_map()
{
    CollectionLight lights(this->_scene.get_punctual_lights());
    std::vector<Photon> photons;
    for(size_t i = 0; i < this->_n_photons; i++)
    {
        PunctualLight light;
        double weight = lights.sample_light(light);

        create_photon_trace(light,weight, photons);
    }

    return PhotonMap(photons);
}

PhotonMapping::PhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel): 
    Render(s), _n_photons(n_photons), _radius(radius), _max_photon_num_per_query(max_photon_num_per_query), _photon_map(create_photon_map()), _kernel(std::move(kernel))
{
    if(n_photons == 0)
        throw std::invalid_argument("The number of photons must be greater than 0.");
}
