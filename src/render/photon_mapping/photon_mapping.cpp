#include <cmath>

#include "render/photon_mapping/photon_mapping.hpp"


PhotonMap PhotonMapping::create_photon_map()
{
    CollectionLight lights(this->_scene.get_punctual_lights(), this->_scene.get_area_lights());
    std::vector<Photon> photons;
    for(size_t i = 0; i < this->_n_photons; i++)
    {
        std::shared_ptr<AbstractLight> light;
        double weight = lights.sample_light(light);

        create_photon_trace(light,weight, photons);
    }

    return PhotonMap(photons);
}

Color PhotonMapping::density_estimate(const IntersectionObject& obj, const BRDFType type) const
{
    Color sum;
    for(const Photon* p : this->_photon_map->nearest_neighbors(obj.get_int_point(), this->_max_photon_num_per_query, this->_radius))
    {
        double distance = (p->get_position() - obj.get_int_point()).norm();
        sum = sum + obj.eval_brdf(p->get_flux()*this->_kernel->eval(distance, this->_radius), p->get_vector(), type);
    }

    return sum;
}

void PhotonMapping::create_photon_trace(const std::shared_ptr<AbstractLight>& light, double weight, std::vector<Photon>& photons)
{
    Ray r = light->sample_ray();

    size_t num_bounces = this->_gc->get_number_of_bounces();

    create_photon_trace_rec(r, Color(4*M_PI*light->luminance_max()/weight), 0, num_bounces, photons);
}

PhotonMapping::PhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel): 
    Render(s), _n_photons(n_photons), _radius(radius), _max_photon_num_per_query(max_photon_num_per_query), _photon_map(nullptr), _kernel(std::move(kernel))
{
    if(n_photons == 0)
        throw std::invalid_argument("The number of photons must be greater than 0.");
}

void PhotonMapping::init_render()
{
    this->_photon_map =std::make_unique<PhotonMap>(create_photon_map());
    this->_initialized = true;
}