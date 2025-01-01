#include "render/render.hpp"

Render::Render(Scene& s)
    : _scene(s), _gc(GlobalConf::get_instance()), _pool(_gc->get_number_of_threads()), _initialized(false)
{}

ColorMap Render::render_scene()
{
    if(!_initialized)
    {
        this->init_render();
        _initialized = true;
    }

    #ifdef METRICS
        Metrics& m = _gc->get_metrics();
        m.start_timer_metric("paint_scene");
        m.add_counter("num_bb_intersections_avoided");
    #endif 

    const std::array<int,2> resolution = this->get_resolution();
    size_t task_size = _gc->get_task_size();
    const size_t num_full_tasks = std::floor(resolution[0]*resolution[1]*1.0/static_cast<double>(task_size));
    size_t rest = (resolution[0]*resolution[1])%task_size;
    const size_t num_real_tasks = rest==0?num_full_tasks:num_full_tasks+1;

    std::vector<std::future<std::vector<Color>>> futures;

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
    
    std::vector<Color> all_colors;
    for(size_t i=0; i<num_real_tasks; ++i)
    {
        std::vector<Color> row_colors = futures[i].get();
        all_colors.insert(std::end(all_colors), std::begin(row_colors), std::end(row_colors));
    }

    if(all_colors.size() != resolution[0]*resolution[1])
        throw std::runtime_error("The number of colors is not the expected.");

    const MatrixSC colors = this->arrange_vector_into_color_matrix(all_colors);

    #ifdef METRICS
        m.finish_timer_metric("paint_scene");
    #endif

    return ColorMap(colors);
}

std::array<int,2> Render::get_resolution() const
{
    return this->_scene.get_resolution();
}

// -------------------------------------------------
// Private methods
// -------------------------------------------------

std::vector<Color> Render::paint_k_pixels(const std::array<size_t,2> start, const size_t n_pixels) const
{
    const std::array<int,2> resolution = this->get_resolution();

    std::vector<Color> colors;
    for(size_t i=0; i<n_pixels; i++)
    {
        const size_t x = (start[1]+i)%resolution[1];
        const size_t y = start[0] + (start[1]+i)/resolution[1];
        colors.push_back(this->compute_pixel_color(x, y));
    }
    return colors;
}

Color Render::compute_pixel_color(const size_t x, const size_t y) const
{
    const size_t num_rays = this->_gc->get_number_of_rays();

    if(num_rays<1)
        throw std::invalid_argument("The number of rays must be greater than 0.");
    
    Color sum = this->compute_random_pixel_color(x, y);
    
    for(size_t i=1; i<num_rays; ++i)
        sum = sum + this->compute_random_pixel_color(x, y);

    return sum/static_cast<double>(num_rays);
}

Color Render::compute_random_pixel_color(const size_t x, const size_t y) const
{
    const std::array<double,2> pixel_coordinates = this->get_random_pixel_coordinates(x,y);
    const Ray r = this->trace_ray(pixel_coordinates);
    const Color l = this->compute_ray_color(r);
    return l;
}

std::array<double,2> Render::get_random_pixel_coordinates(const size_t x, const size_t y) const
{
    const std::array<int,2> resolution = this->get_resolution();
    const double x_coordinate_1 = (1-2.0*x/resolution[0]);
    const double x_coordinate_2 = (1-2.0*(x+1)/resolution[0]);
    const double y_coordinate_1 = (1-2.0*y/resolution[1]);
    const double y_coordinate_2 = (1-2.0*(y+1)/resolution[1]);
    

    return {randomD(x_coordinate_1,x_coordinate_2),
            randomD(y_coordinate_1,y_coordinate_2)};
}

Ray Render::trace_ray(std::array<double,2> coordinates) const
{
    const std::unique_ptr<SpatialElement> p = std::make_unique<Point>(coordinates[0],coordinates[1],1);
    const Camera c = this->_scene.get_camera();
    const Vector dir = (Point(c.transform_to_canonical(p.get()))-c.get_screen_base().get_center());
    const Ray r = Ray(c.get_screen_base().get_center(),dir);
    return r;
}

MatrixSC Render::arrange_vector_into_color_matrix(std::vector<Color> colors) const 
{
    MatrixSC matrix;
    const std::array<int,2> dim = this->get_resolution();
    for (int i = 0; i < dim[1]; ++i) {
        matrix.emplace_back(colors.begin() + i * dim[0], colors.begin() + (i + 1) * dim[0]);
    }

    return matrix;
}

Color Render::calculate_punctual_light_contribution(const IntersectionObject& intersection, BRDFType type) const
{
    const VectorPunctualLight lights = this->_scene.get_punctual_lights();
    Color color_contribution;
    for(const auto & light : lights)
    {
        color_contribution = color_contribution + light->light_contribution(this->_scene.get_objects(), intersection, type);
    }
    return color_contribution;
}