#pragma once


#include "light/kd-tree-photon/photon_map.hpp"
#include "light/collection_light.hpp"
#include "render/render.hpp"
#include "light/photon.hpp"
#include "kernel_density/kernel_density.hpp"


class PhotonMapping final : public Render {
private:
    size_t _n_photons;
    double _radius;
    size_t _max_photon_num_per_query;
    PhotonMap _photon_map;
    std::unique_ptr<Kernel> _kernel;
    
    [[nodiscard]] Color compute_ray_color(const Ray& r) const override;
    PhotonMap create_photon_map();
    void create_photon_trace(const PunctualLight& light, double weight, std::vector<Photon>& photons);
    void create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, std::vector<Photon>& photons);

    Color density_estimate(const IntersectionObject& obj) const;

public:
    explicit PhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel);
};




