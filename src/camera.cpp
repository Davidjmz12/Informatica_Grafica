#include "camera.hpp"

Camera::Camera(Base base, std::array<int,2> resolution)
    : _screen_base(base), _resolution(resolution)
{}

Ray Camera::trace_ray(std::array<float,2> coordinates) const
{
    SpatialElement* p = new Point(coordinates[0],coordinates[1],1);
    Vector dir = (Point(this->c_cam(p))-this->_screen_base.get_center());
    Ray r = Ray(this->_screen_base.get_center(),dir);
    return r;
}

std::array<float,2> Camera::get_random_pixel_coordinates(int x, int y) const
{
    float x_coordinate = (1-2.0*x/this->_resolution[0]);
    float y_coordinate = (1-2.0*y/this->_resolution[1]);

    return {x_coordinate,y_coordinate};
}

Color Camera::compute_pixel_color(int x, int y, int k, std::vector<Geometry*> objects) const
{
    std::array<float,2> pixel_coordinates = this->get_random_pixel_coordinates(x,y);
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

ColorMap Camera::paint_scene(std::vector<Geometry*> objects) const
{
    std::vector<std::vector<Color>> colors;

    for(int i=0;i<this->_resolution[1];i++)
    {
        std::vector<Color> row;
        for(int j=0;j<this->_resolution[0];j++)
        {
            row.push_back(this->compute_pixel_color(j,i,1,objects));
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
