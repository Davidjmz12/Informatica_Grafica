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

Color Camera::compute_pixel_color(int x, int y, int k, std::vector<Geometry*> objects) const
{
    if(k<1)
        throw std::invalid_argument("The number of rays must be greater than 0.");
    
    Color sum = this->compute_random_pixel_color(x,y,objects);
    
    for(unsigned int i=1; i<k; ++i)
        sum = sum + this->compute_random_pixel_color(x,y,objects);

    return sum/k;
}

ColorMap Camera::paint_scene(std::vector<Geometry*> objects, int num_rays) const
{
    std::vector<std::vector<Color>> colors;

    for(int i=0;i<this->_resolution[1];i++)
    {
        std::vector<Color> row;
        for(int j=0;j<this->_resolution[0];j++)
        {
            row.push_back(this->compute_pixel_color(j,i,num_rays,objects));
        }
        colors.push_back(row);
    }

    return ColorMap(colors, RGB);
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
