#pragma once


#include "light/kd-tree-photon/photon_map.hpp"
#include "light/collection_light.hpp"
#include "render/render.hpp"
#include "light/photon.hpp"
#include "kernel_density/kernel_density.hpp"


class PhotonMapping : public Render {
protected:
    size_t _n_photons;
    double _radius;
    size_t _max_photon_num_per_query;
    std::unique_ptr<PhotonMap> _photon_map;
    std::unique_ptr<Kernel> _kernel;
    
    virtual Color compute_ray_color(const Ray& r) const = 0;
    virtual void create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, size_t total_bounces, std::vector<Photon>& photons) = 0;


    PhotonMap create_photon_map();
    void create_photon_trace(const PunctualLight& light, double weight, std::vector<Photon>& photons);
    [[nodiscard]] Color density_estimate(const IntersectionObject& obj) const;

    void init_render() override;
public:
    explicit PhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel);
};




