#pragma once

#include "files/ppm_file.hpp"
#include "spatial_element/base.hpp"

class TextureFacePPM
{
private:
    PpmFile _file;
public:
    TextureFacePPM(const std::string& path):
        _file(PpmFile(path))
    {}

    ColorRGB get_color(const Base& base, const Point& point) const
    {
        Point point_base = Point(base.coord_from_canonical(&point));
        double u = (point_base[1]+1)/2;
        double v = (point_base[2]+1)/2;
        return _file.get_color(u, v);
    }

};