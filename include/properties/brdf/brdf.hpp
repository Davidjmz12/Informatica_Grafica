#pragma once

#include <memory>

#include "color/color.hpp"
#include "scene/ray.hpp"
#include "spatial_element/base.hpp"




class BRDF {
protected:
    Color _k; // The color of the object

public:
    BRDF(Color k);

    BRDF();

    Color get_color() const;
    void set_color(Color k);

    virtual Color eval(Color light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const = 0;

    virtual bool sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) = 0;

    virtual std::string to_string() const = 0;

    virtual bool is_delta() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const BRDF& b);


    virtual ~BRDF() = default;
};
