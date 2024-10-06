#include "geometry/triangle_mesh.hpp"

TriangleMesh::TriangleMesh()
    : _triangles(){}

TriangleMesh::TriangleMesh(std::vector<Triangle> triangles)
    : _triangles(triangles){}


bool TriangleMesh::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    bool intersects = false;
    Intersection min_intersection;
    for(auto triangle : _triangles)
    {
        Intersection one_intersection;
        if(triangle.intersect_with_ray(r, one_intersection))
        {
            if(one_intersection.get_distance() < min_intersection.get_distance())
                min_intersection = one_intersection;
            intersects = true;
        }

    }

    if(intersects)
        intersection = min_intersection;

    return false;
}