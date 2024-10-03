#include "geometry/triangle_mesh.hpp"

TriangleMesh::TriangleMesh(std::vector<Triangle> triangles)
    : _triangles(triangles){}

float TriangleMesh::implicit(Geometric x) const
{
    return 1;
}


bool TriangleMesh::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    bool intersects = false;
    Intersection min_intersection;
    for(auto triangle : _triangles)
    {
        Intersection one_intersection;
        if(triangle.intersect_with_ray(r, one_intersection))
        {
            if(one_intersection.distance() < min_intersection.distance())
                min_intersection = one_intersection;
            intersects = true;
        }

    }

    if(intersects)
        intersection = min_intersection;

    return false;
}