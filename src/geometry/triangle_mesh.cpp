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

    intersection = min_intersection;
    return intersects;

}

std::ostream& operator<<(std::ostream& os, const TriangleMesh& tm)
{
    os << tm.to_string();
    return os;
}

std::string TriangleMesh::to_string() const
{
    std::string s = "TriangleMesh with triangles:\n";
    for(auto triangle : _triangles)
    {
        s += triangle.to_string() + "\n";
    }
    return s;
}