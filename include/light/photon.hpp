#pragma once

#include "spatial_element/point.hpp"
#include "spatial_element/vector.hpp"
#include "color/color.hpp"

class Photon final
{
private:
    Point _position;
    Vector _incident_direction;
    Color _flux;

public:
    Photon(const Point& position, const Vector& incident_direction, const Color& flux);

    [[nodiscard]] Point get_position() const;
    [[nodiscard]] Vector get_vector() const;
    [[nodiscard]] Color get_flux() const;

    double operator[](size_t index) const;
};

struct PhotonAxisPosition
{
    float operator()(const Photon& p, std::size_t i) const
    {
        return p[i];
    }
};
