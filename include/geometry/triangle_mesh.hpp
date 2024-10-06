#pragma once


#include <vector>

#include "geometry/geometry.hpp"
#include "geometry/triangle.hpp"

class TriangleMesh : public Geometry
{
private:
    std::vector<Triangle> _triangles;
    Intersection min_distance(std::vector<Intersection> intersections) const;
public:
    TriangleMesh();

    TriangleMesh(std::vector<Triangle> triangles);

    bool intersect_with_ray(const Ray& r, Intersection& intersection) const;
};