#include "scene/render.hpp"

Render::Render(Scene s)
    : _scene(s), _gc(GlobalConf::get_instance()), _pool(_gc->get_number_of_threads())
{}

ColorMap Render::render_scene()
{
    if(_gc->has_metrics())
    {
        Metrics& m = _gc->get_metrics();
        m.start_timer_metric("paint_scene");
    }

    std::array<int,2> resolution = this->get_resolution();
    size_t task_size = _gc->get_task_size();
    size_t num_full_tasks = std::floor(resolution[0]*resolution[1]*1.0/task_size);
    size_t rest = (resolution[0]*resolution[1])%task_size;
    size_t num_real_tasks = rest==0?num_full_tasks:num_full_tasks+1;

    std::vector<std::future<std::vector<SpectralColor>>> futures;

    for(size_t i=0; i<num_full_tasks; ++i)
    {
        std::array<size_t,2> start = {(i*task_size)/resolution[1],(i*task_size)%resolution[1]};
        futures.push_back(
            this->_pool.enqueue(
                [this, start,task_size](){
                    return this->paint_k_pixels(start, task_size);
                }
            )
        );
    }

    if(rest != 0)
    {
        std::array<size_t,2> start = {(num_full_tasks*task_size)/resolution[1],(num_full_tasks*task_size)%resolution[1]};
        futures.push_back(
            this->_pool.enqueue(
                [this,rest,start](){
                    return this->paint_k_pixels(start, rest);
                }
            )
        );
    }
    
    std::vector<SpectralColor> all_colors;
    for(size_t i=0; i<num_real_tasks; ++i)
    {
        std::vector<SpectralColor> row_colors = futures[i].get();
        all_colors.insert(std::end(all_colors), std::begin(row_colors), std::end(row_colors));
    }

    if(all_colors.size() != resolution[0]*resolution[1])
        throw std::runtime_error("The number of colors is not the expected.");
    
    MatrixSC colors = this->arrange_vector_into_color_matrix(all_colors);

    if(_gc->has_metrics())
    {
        Metrics& m = _gc->get_metrics();
        m.finish_timer_metric("paint_scene");
    }

    return ColorMap(colors); 
}

std::array<int,2> Render::get_resolution() const
{
    return this->_scene.get_resolution();
}

// -------------------------------------------------
// Private methods
// -------------------------------------------------

std::vector<SpectralColor> Render::paint_k_pixels(std::array<size_t,2> start, size_t k) const
{
    std::array<int,2> resolution = this->get_resolution();

    std::vector<SpectralColor> colors;
    for(size_t i=0; i<k; i++)
    {
        size_t x = (start[1]+i)%resolution[1];
        size_t y = start[0] + (start[1]+i)/resolution[1];
        colors.push_back(this->compute_pixel_color(x, y));
    }
    return colors;
}

SpectralColor Render::compute_pixel_color(int x, int y) const
{
    size_t num_rays = this->_gc->get_number_of_rays();

    if(num_rays<1)
        throw std::invalid_argument("The number of rays must be greater than 0.");
    
    SpectralColor sum = this->compute_random_pixel_color(x, y);
    
    for(size_t i=1; i<num_rays; ++i)
        sum = sum + this->compute_random_pixel_color(x, y);

    return sum/num_rays;
}

SpectralColor Render::compute_random_pixel_color(int x, int y) const
{
    std::array<double,2> pixel_coordinates = this->get_random_pixel_coordinates(x,y);
    Ray r = this->trace_ray(pixel_coordinates);
    IndirectLight l = this->compute_ray_intersection_color(r, _gc->get_number_of_bounces()); 
    return l.light_contribution;
}

IndirectLight Render::compute_ray_intersection_color(Ray r, size_t n_rec) const
{
    // If the number of bounces is 0, return black.
    if(n_rec == 0)
        return IndirectLight{Point(), SpectralColor(0.0)};

    IntersectionObject min_int_obj;

    bool intersects = false;

    for(auto element: this->_scene.get_objects())
    {
        IntersectionObject int_obj_aux;
        if(element->intersect_with_ray(r, int_obj_aux))
        {
            intersects = true;
            if(int_obj_aux < min_int_obj)
                min_int_obj = int_obj_aux;
        }
    }

    IntersectionLight min_int_light;
    for(auto element: this->_scene.get_area_lights())
    {
        IntersectionLight int_light_aux;
        if(element->intersect_with_ray(r, int_light_aux))
        {
            intersects = true;
            if(int_light_aux < min_int_light)
                min_int_light = int_light_aux;
        }
    }

    // If the ray does not intersect with any object, return black.
    if(!intersects)
        return IndirectLight{Point(), SpectralColor(0.0)};


    if(min_int_light < min_int_obj)
    {
        return IndirectLight{min_int_light.get_point(),min_int_light.get_power()};
    } else 
    {
        Ray new_ray = sample_new_random_ray(min_int_obj);
        IndirectLight indirect_light = compute_ray_intersection_color(new_ray, n_rec-1);
        SpectralColor indirect_light_contribution = min_int_obj.evalRenderEquation(indirect_light.light_contribution, indirect_light.origin);
        SpectralColor point_light_contribution = calculate_total_light(min_int_obj);

        return IndirectLight{min_int_obj.get_point(), point_light_contribution + indirect_light_contribution};
    }

}

SpectralColor Render::calculate_total_light(IntersectionObject& intersection) const
{
    std::vector<PunctualLight*> lights = this->_scene.get_punctual_lights();
    SpectralColor color_contribution;
    for(size_t i=0; i<lights.size(); ++i)
    {
        color_contribution = color_contribution + lights[i]->light_contribution(this->_scene.get_objects(), intersection);
    }
    return color_contribution;
}

Ray Render::sample_new_random_ray(IntersectionObject& intersection) const
{
    double phi = randomD(0,2*M_PI);
    double theta = randomD(0,1);
    theta = acos(sqrt(1-theta));

    Base b = Base::complete_base_k(intersection.get_point(),intersection.get_normal());

    Vector v = Vector(b.coord_into_canonical(new Vector(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta))));
    return Ray(intersection.get_point(),v);
}

std::array<double,2> Render::get_random_pixel_coordinates(int x, int y) const
{
    std::array<int,2> resolution = this->get_resolution();
    double x_coordinate_1 = (1-2.0*x/resolution[0]);
    double x_coordinate_2 = (1-2.0*(x+1)/resolution[0]);
    double y_coordinate_1 = (1-2.0*y/resolution[1]);
    double y_coordinate_2 = (1-2.0*(y+1)/resolution[1]);
    

    return {randomD(x_coordinate_1,x_coordinate_2),
            randomD(y_coordinate_1,y_coordinate_2)};
}

Ray Render::trace_ray(std::array<double,2> coordinates) const
{
    SpatialElement* p = new Point(coordinates[0],coordinates[1],1);
    Camera c = this->_scene.get_camera();
    Vector dir = (Point(c.transform_to_canonical(p))-c.get_screen_base().get_center());
    Ray r = Ray(c.get_screen_base().get_center(),dir);
    return r;
}

MatrixSC Render::arrange_vector_into_color_matrix(std::vector<SpectralColor> colors) const 
{
    MatrixSC matrix;
    std::array<int,2> dim = this->get_resolution();
    for (int i = 0; i < dim[1]; ++i) {
        matrix.push_back(std::vector<SpectralColor>(colors.begin() + i * dim[0], colors.begin() + (i + 1) * dim[0]));
    }

    return matrix;
}