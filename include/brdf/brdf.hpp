#pragma once

#include <memory>
#include <optional>
#include <variant>

#include "color/color.hpp"
#include "scene/ray.hpp"
#include "spatial_element/base.hpp"
#include "geometry/textures/texture.hpp"

enum class BRDFType {
    ABSORPTION,
    DIFFUSE,
    SPECULAR,
    TRANSMISSIVE,
};

class BRDF {
private:
    Color _kd; // The diffuse color of the object
    std::optional<std::shared_ptr<Texture>> _kd_texture; // The diffuse color of the object

    Color _ks; // The specular color of the object

    Color _kt; // The transmission color of the object
    double _refraction_index; // The refraction index of the object

    Color _ke; // The emission color of the object
    
    std::array<double,3> _weights; // The weights of the different components of the BRDF

    bool sample_diffuse(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const;
    bool sample_specular(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const;
    bool sample_transmissive(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const;

public:

    static BRDF create_diffuse_BRDF(Color k);
    static BRDF create_diffuse_BRDF(Color k, std::shared_ptr<Texture> kd_texture);
    static BRDF create_specular_BRDF(Color k);
    static BRDF create_transmissive_BRDF(Color k, double refraction_index);
    static BRDF create_emisive_BRDF(Color k);
    
    BRDF();
    BRDF(Color kd, Color ks, Color kt, double refraction_index, Color ke);
    BRDF(Color kd, Color ks, Color kt, double refraction_index, Color ke, std::shared_ptr<Texture> kd_texture);

    Color get_emission() const;

    Color eval(Color light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry, double u, double v, BRDFType sampled) const;

    BRDFType sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const;

    std::string to_string() const;

    static bool is_delta(BRDFType t);
    
    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);

};
