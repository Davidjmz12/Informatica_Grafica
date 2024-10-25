#include "camera.hpp"

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
    Intersection min_int;
    bool intersects = false;
    for(auto element: objects)
    {
        Intersection aux_int;
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

ColorMap Camera::paint_scene(std::vector<Geometry*> objects, std::vector<Light> lights) const
{   
    GlobalConf *gc = GlobalConf::get_instance();
    if(gc->has_metrics())
    {
        Metrics& m = gc->get_metrics();
        m.start_timer_metric("paint_scene");
    }
    size_t num_threads = gc->get_number_of_threads();

    ThreadPool pool(num_threads);

    std::vector<std::future<std::vector<SpectralColor>>> futures;

    for(size_t i=0; i<this->_resolution[0]; ++i)
    {
        futures.push_back(
            pool.enqueue(
                [this,objects,lights,i](){
                    return this->paint_one_row(objects, lights, i);
                }
            )
        );
    }

    MatrixSC colors;
    for(size_t i=0; i<this->_resolution[0]; ++i)
    {
        std::vector<SpectralColor> row_colors = futures[i].get();
        colors.push_back(row_colors);
    }

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


SpectralColor Camera::compute_final_color(Intersection intersec, 
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
