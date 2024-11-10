#include "geometry/mesh.hpp"

Mesh::Mesh()
    : _elements(), Geometry()
{}

Mesh::Mesh(std::vector<Geometry*> elements):
    Geometry(), _elements(elements)
{}

Mesh::Mesh(std::vector<Geometry*> elements, BoundingBox bounding_box)
    : Geometry(), _elements(elements), _bounding_box(bounding_box)
{
    GlobalConf *gc = GlobalConf::get_instance();
    if(gc->has_metrics())
    {
        Metrics& m = gc->get_metrics();
        //m.init_time_metric("mesh_intersection", "Time doing intersection with mesh");
        m.add_counter("mesh_intersections_avoided", "Number of intersections avoided with bounding box");
    }
}


BoundingBox Mesh::get_bounding_box() const
{
    if(!this->_bounding_box.has_value())
        throw std::invalid_argument("The bounding box has not been set for this mesh");
    
    return _bounding_box.value();
}

bool Mesh::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    if(_bounding_box.has_value())
    {
        if(!_bounding_box.value().intersect_with_ray(r))
        {
            if(GlobalConf::get_instance()->has_metrics())
            {
                Metrics& m = GlobalConf::get_instance()->get_metrics();
                m.increment_counter("mesh_intersections_avoided");
            }
            return false;
        } 
    }

    bool intersects = false;
    IntersectionObject min_intersection;
    for(auto element : _elements)
    {
        IntersectionObject one_intersection;
        if(element->intersect_with_ray(r, one_intersection))
        {
            if(one_intersection < intersection)
                intersection = one_intersection;
            intersects = true;
        }

    }
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