#include <cmath>

#include "render/photon_mapping/photon_mapping.hpp"


PhotonMap PhotonMapping::create_photon_map()
{
    #ifdef METRICS
    Metrics& m = GlobalConf::get_instance()->get_metrics();
    m.init_time_metric("create_photon_map", "Time to create the photon map");
    m.start_duration_time_metric("create_photon_map");
    #endif
    std::vector<std::future<std::vector<Photon>>> futures(this->_gc->get_number_of_threads());
    
    CollectionLight lights(this->_scene.get_punctual_lights(), this->_scene.get_area_lights());

    size_t num_photons_per_thread = this->_n_photons / this->_gc->get_number_of_threads();
    size_t num_photons_last_thread = num_photons_per_thread + this->_n_photons % this->_gc->get_number_of_threads();

    // Launch tasks
    for (size_t i = 0; i < this->_gc->get_number_of_threads(); i++) {
        size_t n = (i == this->_gc->get_number_of_threads() - 1) ? num_photons_last_thread : num_photons_per_thread;
        futures[i] = (
            this->_pool.enqueue(
                [this, &lights, n]() {
                    return this->trace_n_photons(n, lights);
                }
            )
        );
    }

    // Reserve space for all photons (we know the total count)
    std::vector<Photon> photons;
    photons.reserve(this->_n_photons);

    // Collect photons from all threads
    for (auto& future : futures) {
        std::vector<Photon> photons_thread = future.get();
        photons.insert(photons.end(), 
                    std::make_move_iterator(photons_thread.begin()), 
                    std::make_move_iterator(photons_thread.end()));
    }

    #ifdef METRICS
    m.add_duration_to_time_metric("create_photon_map");

    m.init_time_metric("create_kd_tree", "Time to create the KD-tree");
    m.start_duration_time_metric("create_kd_tree");
    #endif

    PhotonMap pm(std::move(photons));

    #ifdef METRICS
    m.add_duration_to_time_metric("create_kd_tree");
    #endif

    return pm;
}

std::vector<Photon> PhotonMapping::trace_n_photons(const size_t n, const CollectionLight& lights) const
{
    
    std::vector<Photon> photons;
    for(size_t i = 0; i < n; i++)
    {
        std::shared_ptr<AbstractLight> light;
        double weight = lights.sample_light(light);

        create_photon_trace(light, weight, photons);
    }
    return photons;
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

void PhotonMapping::create_photon_trace(const std::shared_ptr<AbstractLight>& light, double weight, std::vector<Photon>& photons) const
{
    Ray r = light->sample_ray();

    size_t num_bounces = this->_gc->get_number_of_bounces();

    create_photon_trace_rec(r, Color(4*M_PI*weight/this->_n_photons), 0, num_bounces, photons);
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