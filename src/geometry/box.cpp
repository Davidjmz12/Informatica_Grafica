#include "geometry/box.hpp"

Box::Box(Point center, std::array<double,3> sides, std::array<Vector,3> axis, Property properties)
    : Geometry(properties)
{
    if(sides[0]<=0 || sides[1]<=0 || sides[2]<=0)
        throw std::invalid_argument("The sides of the box must be positive");
    if(neqD(axis[0].norm(),1) || neqD(axis[1].norm(),1) || neqD(axis[2].norm(),1))
        throw std::invalid_argument("The axis of the box must be normalized.");
    if(!axis[0].is_base(axis[1],axis[2]))
        throw std::invalid_argument("The axis of the box must be a R^3 base.");
    
    std::vector<Geometry*> elements;
    elements = {
        new Face(axis[0], axis[1]*sides[1], axis[2]*sides[2], center + axis[0]*sides[0], properties),
        new Face(axis[0], axis[1]*sides[1], axis[2]*sides[2], center - axis[0]*sides[0], properties),
        new Face(axis[1], axis[0]*sides[0], axis[2]*sides[2], center + axis[1]*sides[1], properties),
        new Face(axis[1], axis[0]*sides[0], axis[2]*sides[2], center - axis[1]*sides[1], properties),
        new Face(axis[2], axis[0]*sides[0], axis[1]*sides[1], center + axis[2]*sides[2], properties),
        new Face(axis[2], axis[0]*sides[0], axis[1]*sides[1], center - axis[2]*sides[2], properties)
    };

    BoundingBox b = BoundingBox({
                                 center[0]-sides[0],center[0]+sides[0],
                                 center[1]-sides[1],center[1]+sides[1],
                                 center[2]-sides[2],center[2]+sides[2]
                                 });

    _mesh = Mesh(elements, b);
}


BoundingBox Box::get_bounding_box() const
{
    return _mesh.get_bounding_box();
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