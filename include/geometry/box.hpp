#pragma once

#include <array>

#include "geometry/triangle_mesh.hpp"

class Box : public Geometry
{
private:
    TriangleMesh _mesh;
public:
    Box(Point center, std::array<double,3> sides, std::array<Vector,3> axis);

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};