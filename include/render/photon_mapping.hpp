#pragma once


#include "light/kd-tree-photon/photon_map.hpp"
#include "light/collection_light.hpp"
#include "render/render.hpp"
#include "light/photon.hpp"


class PhotonMapping final : public Render {
private:
    size_t _n_photons;
    PhotonMap _photon_map;
    
    [[nodiscard]] SpectralColor compute_ray_color(const Ray& r) const override;
    PhotonMap create_photon_map();
    void create_photon_trace(const PunctualLight& light, double weight, std::vector<Photon>& photons);
    void create_photon_trace_rec(const Ray& r, SpectralColor flux, size_t num_bounces, std::vector<Photon>& photons);

    SpectralColor density_estimate(const IntersectionObject& obj) const;

public:
    explicit PhotonMapping(Scene& s, size_t n_photons);
};




