#include "camera.hpp"

Camera::Camera(Base base, unsigned int width, unsigned int height, double distance)
    : _screen_base(base.normalize()), _width(width), _height(height), 
    _distance(distance), _camera(_screen_base.coord_into_canonical(new Point(width/2.0,height/2.0,0)))
{
    if (width <= 0 || height <= 0 || distance <= 0)
        throw std::invalid_argument("Width, height and distance must be positive numbers.");
}

Ray Camera::trace_ray(double x, double y) const
{
    Ray r = Ray( this->_camera,
                (Point)this->_screen_base.coord_into_canonical(
                    new Point(x,y,this->_distance)) -
                    this->_camera);
    return r;
}

Color Camera::compute_pixel_color(int x, int y, int k, std::vector<Geometry*> objects) const
{
    Color mean_color();
    Ray r = this->trace_ray(x,y);
    Intersection min_int;
    bool intersects = false;
    for(auto element: objects)
    {
        Intersection aux_int;
        if(element->intersect_with_ray(r, aux_int))
        {
            intersects = true;
            if(aux_int.get_distance() < min_int.get_distance())
                min_int = aux_int;
        }
    }
    if(intersects)
    {
        Vector v = (min_int.get_normal().normalize()+Vector(1,1,1))/2*255;
        return Color({v[0],v[1],v[2]},Color::RGB_255_RANGE,RGB);
    } else {
        return Color();
    }
}

ColorMap Camera::paint_scene(std::vector<Geometry*> objects) const
{
    std::vector<std::vector<Color>> colors;

    for(unsigned int i=0;i<this->_height;i++)
    {
        std::vector<Color> row;
        for(unsigned int j=0;j<this->_width;j++)
        {
            row.push_back(this->compute_pixel_color(i,j,1,objects));
        }
        colors.push_back(row);
    }

    return ColorMap(colors, RGB);
}

SpatialElement* Camera::c_cam(const SpatialElement* s) const
{
    return this->_screen_base.coord_into_canonical(s);
}

std::ostream& operator<<(std::ostream& os, Camera c)
{
    os << "Camera:" << std::endl;
    os << c._screen_base << std::endl;
    os << "Dimensions: " << c._width << "x" << c._height << std::endl;
    os << "Distance: " << c._distance; 

    return os;
}
