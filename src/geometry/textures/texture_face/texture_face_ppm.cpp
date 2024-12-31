#pragma once

#include "geometry/textures/texture_face/texture_face_ppm.hpp"

TextureFacePPM::TextureFacePPM(const std::string& path):
    _file(PpmFile(path))
{}

ColorRGB TextureFacePPM::get_color(const Base& base, const Point& point) const
{
    Point point_base = Point(base.coord_from_canonical(&point));
    double u = point_base[1], v = point_base[2];
    u *= _file.get_dimension()[0];
    v *= _file.get_dimension()[1];

    return _file.get_color(static_cast<int>(floor(u)),static_cast<int>(floor(v)));
}
