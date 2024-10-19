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

Color Camera::compute_random_pixel_color(int x, int y, std::vector<Geometry*> objects) const
{
    std::array<double,2> pixel_coordinates = this->get_random_pixel_coordinates(x,y);
    Ray r = this->trace_ray(pixel_coordinates);
    Intersection min_int;
    for(auto element: objects)
    {
        Intersection aux_int;
        if(element->intersect_with_ray(r, aux_int))
        {
            if(aux_int < min_int)
                min_int = aux_int;
        }
    }
    return min_int.get_properties().get_color();
}

Color Camera::compute_pixel_color(int x, int y, std::vector<Geometry*> objects) const
{
    size_t num_rays = GlobalConf::get_instance()->get_number_of_rays();

    if(num_rays<1)
        throw std::invalid_argument("The number of rays must be greater than 0.");
    
    Color sum = this->compute_random_pixel_color(x,y,objects);
    
    for(size_t i=1; i<num_rays; ++i)
        sum = sum + this->compute_random_pixel_color(x,y,objects);

    return sum/num_rays;
}

std::vector<Color> Camera::paint_one_row(std::vector<Geometry*> objects,  size_t row) const
{
    std::vector<Color> colors;
    for(size_t i=0;i<this->_resolution[1];i++)
    {
        colors.push_back(this->compute_pixel_color(i, row, objects));
    }
    return colors;
}

ColorMap Camera::paint_scene(std::vector<Geometry*> objects) const
{   
    size_t num_threads = GlobalConf::get_instance()->get_number_of_threads();

    ThreadPool pool(num_threads);

    std::vector<std::future<std::vector<Color>>> futures;

    for(size_t i=0; i<this->_resolution[0]; ++i)
    {
        futures.push_back(
            pool.enqueue(
                [this,objects,i](){
                    return this->paint_one_row(objects,i);
                }
            )
        );
    }

    std::vector<std::vector<Color>> colors;
    for(size_t i=0; i<this->_resolution[0]; ++i)
    {
        std::vector<Color> row_colors = futures[i].get();
        colors.push_back(row_colors);
    }

    return ColorMap(colors,RGB);
}

SpatialElement* Camera::c_cam(const SpatialElement* s) const
{
    return this->_screen_base.coord_into_canonical(s);
}

std::array<int,2> Camera::get_resolution() const
{
    return this->_resolution;
}

std::ostream& operator<<(std::ostream& os, Camera c)
{
    os << "Camera:" << std::endl;
    return os;
}
