#include "scene/camera.hpp"

Camera::Camera(Base base, std::array<int,2> resolution)
    : _screen_base(base), _resolution(resolution)
{}

Ray Camera::trace_ray(std::array<double,2> coordinates) const
{
    SpatialElement* p = new Point(coordinates[0],coordinates[1],1);
    Vector dir = (Point(this->c_cam(p))-this->_screen_base.get_center());
    Ray r = Ray(this->_screen_base.get_center(),dir);
    return r;
}

std::array<double,2> Camera::get_random_pixel_coordinates(int x, int y) const
{
    double x_coordinate_1 = (1-2.0*x/this->_resolution[0]);
    double x_coordinate_2 = (1-2.0*(x+1)/this->_resolution[0]);
    double y_coordinate_1 = (1-2.0*y/this->_resolution[1]);
    double y_coordinate_2 = (1-2.0*(y+1)/this->_resolution[1]);
    

    return {randomD(x_coordinate_1,x_coordinate_2),
            randomD(y_coordinate_1,y_coordinate_2)};
}

SpectralColor Camera::compute_random_pixel_color(int x, int y, std::vector<Geometry*> objects, std::vector<Light> lights) const
{
    std::array<double,2> pixel_coordinates = this->get_random_pixel_coordinates(x,y);
    Ray r = this->trace_ray(pixel_coordinates);
    IntersectionObject min_int;
    bool intersects = false;
    for(auto element: objects)
    {
        IntersectionObject aux_int;
        if(element->intersect_with_ray(r, aux_int))
        {
            intersects = true;
            if(aux_int < min_int)
                min_int = aux_int;
        }
    }
    if(!intersects)
        return SpectralColor();
    
    SpectralColor final_color = compute_final_color(min_int, objects, lights);
    return final_color;
}

SpectralColor Camera::compute_pixel_color(int x, int y, std::vector<Geometry*> objects,  std::vector<Light> lights) const
{
    size_t num_rays = GlobalConf::get_instance()->get_number_of_rays();

    if(num_rays<1)
        throw std::invalid_argument("The number of rays must be greater than 0.");
    
    SpectralColor sum = this->compute_random_pixel_color(x, y, objects, lights);
    
    for(size_t i=1; i<num_rays; ++i)
        sum = sum + this->compute_random_pixel_color(x, y, objects, lights);

    return sum/num_rays;
}

std::vector<SpectralColor> Camera::paint_one_row(std::vector<Geometry*> objects,  std::vector<Light> lights,  size_t row) const
{
    std::vector<SpectralColor> colors;
    for(size_t i=0;i<this->_resolution[1];i++)
    {
        colors.push_back(this->compute_pixel_color(i, row, objects, lights));
    }
    return colors;
}

std::vector<SpectralColor> Camera::paint_k_pixels(std::vector<Geometry*> objects, std::vector<Light> lights, 
    std::array<size_t,2> start, size_t k) const
{
    std::vector<SpectralColor> colors;
    for(size_t i=0; i<k; i++)
    {
        size_t x = (start[1]+i)%this->_resolution[1];
        size_t y = start[0] + (start[1]+i)/this->_resolution[1];
        colors.push_back(this->compute_pixel_color(x, y, objects, lights));
    }
    return colors;
}

MatrixSC createMatrix(std::array<int,2> dim, std::vector<SpectralColor> colors) {

    // Initialize a std::vector of std::vector<int> with each row pointing to part of 'data'
    MatrixSC matrix;

    for (int i = 0; i < dim[1]; ++i) {
        matrix.push_back(std::vector<SpectralColor>(colors.begin() + i * dim[0], colors.begin() + (i + 1) * dim[0]));
    }

    return matrix;
}


ColorMap Camera::paint_scene(std::vector<Geometry*> objects, std::vector<Light> lights) const
{   
    GlobalConf *gc = GlobalConf::get_instance();
    if(gc->has_metrics())
    {
        Metrics& m = gc->get_metrics();
        m.start_timer_metric("paint_scene");
    }
    size_t num_threads = gc->get_number_of_threads();
    size_t task_size = gc->get_task_size();
    size_t num_full_tasks = std::floor(this->_resolution[0]*this->_resolution[1]*1.0/task_size);
    size_t rest = (this->_resolution[0]*this->_resolution[1])%task_size;
    size_t num_real_tasks = rest==0?num_full_tasks:num_full_tasks+1;
    ThreadPool pool(num_threads);

    std::vector<std::future<std::vector<SpectralColor>>> futures;

    for(size_t i=0; i<num_full_tasks; ++i)
    {
        std::array<size_t,2> start = {(i*task_size)/this->_resolution[1],(i*task_size)%this->_resolution[1]};
        futures.push_back(
            pool.enqueue(
                [this,objects,lights,start,task_size](){
                    return this->paint_k_pixels(objects, lights, start, task_size);
                }
            )
        );
    }


    if(rest != 0)
    {
        std::array<size_t,2> start = {(num_full_tasks*task_size)/this->_resolution[1],(num_full_tasks*task_size)%this->_resolution[1]};
        futures.push_back(
            pool.enqueue(
                [this,objects,lights,rest,start](){
                    return this->paint_k_pixels(objects, lights, start, rest);
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

    if(all_colors.size() != this->_resolution[0]*this->_resolution[1])
        throw std::runtime_error("The number of colors is not the expected.");
    
    MatrixSC colors = createMatrix(this->_resolution, all_colors);
    if(gc->has_metrics())
    {
        Metrics& m = gc->get_metrics();
        m.finish_timer_metric("paint_scene");
    }

    return ColorMap(colors);
}

SpatialElement* Camera::c_cam(const SpatialElement* s) const
{
    return this->_screen_base.coord_into_canonical(s);
}

std::array<int,2> Camera::get_resolution() const
{
    return this->_resolution;
}


SpectralColor Camera::compute_final_color(IntersectionObject intersec, 
    std::vector<Geometry*> objects, std::vector<Light> lights) const
{
    SpectralColor final_color = lights[0].meets_light(objects, intersec);
    for(size_t i=1; i<lights.size(); ++i)
    {
        final_color = final_color + lights[i].meets_light(objects, intersec);
    }
    return final_color;
}

std::ostream& operator<<(std::ostream& os, Camera c)
{
    os << "Camera:" << std::endl;
    return os;
}
