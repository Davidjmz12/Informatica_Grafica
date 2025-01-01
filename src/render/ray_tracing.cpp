#include "render/ray_tracing.hpp"


RayTracing::RayTracing(Scene& s) : 
    Render(s) 
{}

Color RayTracing::compute_ray_color(const Ray& r) const
{
    return compute_ray_intersection_color(r, this->_gc->get_number_of_bounces());
}

Color RayTracing::compute_ray_intersection_color(const Ray& r, const size_t n_rec) const
{
    // If the number of bounces is 0, return black.
    if(n_rec == 0)
        return Color{};

    IntersectionObject min_int_obj;

    bool intersects = false;

    intersects = this->_scene.intersect_with_ray(r, min_int_obj);

    IntersectionLight min_int_light;
    for(const auto& element: this->_scene.get_area_lights())
    {
        if(IntersectionLight int_light_aux; element->intersect_with_ray(r, int_light_aux))
        {
            intersects = true;
            if(int_light_aux < min_int_light)
                min_int_light = int_light_aux;
        }
    }

    // If the ray does not intersect with any object, return black.
    if(!intersects)
        return Color();


    if(min_int_light < min_int_obj)
    {
        return min_int_light.get_power();
    }

    Ray new_ray;
    BRDFType sampled = min_int_obj.sample_ray(new_ray);
    if(sampled == BRDFType::ABSORPTION)
        return Color{};

    const Color indirect_light = compute_ray_intersection_color(new_ray, n_rec-1);
    const Color indirect_light_contribution = min_int_obj.eval_brdf(indirect_light, new_ray.get_direction(), sampled);
    Color point_light_contribution;
    if(!BRDF::is_delta(sampled))
    {
        point_light_contribution = calculate_punctual_light_contribution(min_int_obj, sampled);
    } 
    return point_light_contribution + indirect_light_contribution;
}

void RayTracing::init_render()
{
    this->_initialized = true;
}