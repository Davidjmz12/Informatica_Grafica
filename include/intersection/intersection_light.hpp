#pragma once

#include "intersection/intersection.hpp"
#include "color/color.hpp"


class IntersectionLight : public Intersection
{
private:
    Color _power;

public:
    IntersectionLight();
        
    IntersectionLight(double distance, Color power, Point intersection_point, Ray ray);

    Color get_power() const;

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const IntersectionLight& i);
};
