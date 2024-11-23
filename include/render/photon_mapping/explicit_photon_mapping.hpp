#pragma once

#include "render/photon_mapping/photon_mapping.hpp"

class ExplicitPhotonMapping final : public PhotonMapping {
public:
    ExplicitPhotonMapping(Scene& s, size_t n_photons, size_t max_photon_num_per_query, double radius, std::unique_ptr<Kernel> kernel);
private:

    [[nodiscard]] Color compute_ray_color(const Ray& r) const override;
    void create_photon_trace_rec(const Ray& r, Color flux, size_t num_bounces, size_t total_bounces, std::vector<Photon>& photons) override;
};