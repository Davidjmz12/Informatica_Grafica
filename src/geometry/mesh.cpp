#include "geometry/mesh.hpp"

Mesh::Mesh()
    : _elements(), Geometry()
{}

Mesh::Mesh(std::vector<Geometry*> elements)
    : Geometry(), _elements(elements)
{}

Mesh::Mesh(std::vector<Geometry*> elements, BoundingBox bounding_box)
    : Geometry(), _elements(elements), _bounding_box(bounding_box)
{}

bool Mesh::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    if(_bounding_box.has_value())
    {
        if(!_bounding_box.value().intersect_with_ray(r))
            return false;
    }

    bool intersects = false;
    Intersection min_intersection;
    for(auto element : _elements)
    {
        Intersection one_intersection;
        if(element->intersect_with_ray(r, one_intersection))
        {
            if(one_intersection < min_intersection)
                min_intersection = one_intersection;
            intersects = true;
        }

    }

    intersection = min_intersection;
    return intersects;

}

std::ostream& operator<<(std::ostream& os, const Mesh& tm)
{
    os << tm.to_string();
    return os;
}

std::string Mesh::to_string() const
{
    std::string s = "Mesh with elements:\n\t";
    for(auto element : _elements)
    {
        s += element->to_string() + "\n\t";
    }
    return s;
}