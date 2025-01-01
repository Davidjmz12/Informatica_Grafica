#pragma once

#include "files/ppm_file.hpp"
#include "spatial_element/base.hpp"
#include "geometry/textures/texture.hpp"

class TexturePPM : public Texture
{
private:
    PpmFile _file;
public:
    TexturePPM(const std::string& path):
        _file(PpmFile(path))
    {}

    Color get_color(double u, double v) const override
    {
        return _file.get_color(u,v);
    }

};