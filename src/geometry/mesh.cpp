#include "geometry/mesh.hpp"

Mesh::Mesh():
    Geometry(), _kd_tree()
{}

Mesh::Mesh(VectorGeometries elements, const size_t depth):
    Geometry(), _kd_tree(KDTree(elements, depth))
{}


BoundingBox Mesh::get_bounding_box() const
{
    return this->_kd_tree.root->bbox;
}

bool Mesh::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    return _kd_tree.intersect_with_ray(r, intersection);
}

Ray Mesh::sample_ray() const
{
    VectorGeometries geometries = _kd_tree.get_geometries();
    size_t index = randomI(0, geometries.size()-1);

    return geometries[index]->sample_ray();
}

std::ostream& operator<<(std::ostream& os, const Mesh& tm)
{
    os << tm.to_string();
    return os;
}

std::string Mesh::to_string() const
{
    std::string s = "Mesh with tree:" + this->_kd_tree.to_string();  
    return s;
}