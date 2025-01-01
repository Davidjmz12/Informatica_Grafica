#pragma once

class Texture {
public:
    virtual Color get_color(Point p, Vector n, double u, double v) const = 0;
};