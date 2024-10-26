#include "geometry/box.hpp"

Box::Box(Point center, std::array<Vector,3> axis, Property properties)
    : Geometry(properties)
{
    if(!axis[0].is_base(axis[1],axis[2]))
        throw std::invalid_argument("The axis of the box must be a R^3 base.");
    
    std::vector<Geometry*> elements;
    elements = {
        new Face(axis[0], axis[1], axis[2], center + axis[0], properties),
        new Face(axis[0], axis[1], axis[2], center - axis[0], properties),
        new Face(axis[1], axis[0], axis[2], center + axis[1], properties),
        new Face(axis[1], axis[0], axis[2], center - axis[1], properties),
        new Face(axis[2], axis[0], axis[1], center + axis[2], properties),
        new Face(axis[2], axis[0], axis[1], center - axis[2], properties)
    };

    _mesh = Mesh(elements);

    std::vector<Point> corners;
    for(size_t i:{0,1})
        for(size_t j:{0,1})
            for(size_t k:{0,1})
                corners.push_back(center + axis[0]*i + axis[1]*j + axis[2]*k);
    
    _bounding_box = BoundingBox::get_BB_by_corners(corners);
}

BoundingBox Box::get_bounding_box() const
{
    return _bounding_box;
}

bool Box::intersect_with_ray(const Ray& r, Intersection& intersection) const
{
    return _mesh.intersect_with_ray(r, intersection);
}

std::ostream& operator<<(std::ostream& os, const Box& b)
{
    os << b.to_string(); 
    return os;
}

std::string Box::to_string() const
{
    return "Box with mesh:\n" + this->_mesh.to_string();
}