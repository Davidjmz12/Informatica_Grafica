#pragma once

#include <array>

#include "geometry/triangle_mesh.hpp"

class Box : public Geometry
{
private:
    TriangleMesh _mesh;
public:
    Box(Geometric center, std::array<float,3> sides, std::array<Geometric,3> axis);

    float implicit(Geometric x) const;

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};