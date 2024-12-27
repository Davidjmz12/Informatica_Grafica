#include "geometry/box.hpp"

Box::Box(const Point& center, std::array<Vector,3> axis, std::shared_ptr<Property> properties)
    : Geometry(properties)
{
    if(!axis[0].is_base(axis[1],axis[2]))
        throw std::invalid_argument("The axis of the box must be a R^3 base.");

    const VectorGeometries elements = {
        std::make_shared<Face>(axis[0], axis[1], axis[2], center + axis[0], properties),
        std::make_shared<Face>(axis[0], axis[1], axis[2], center - axis[0], properties),
        std::make_shared<Face>(axis[1], axis[0], axis[2], center + axis[1], properties),
        std::make_shared<Face>(axis[1], axis[0], axis[2], center - axis[1], properties),
        std::make_shared<Face>(axis[2], axis[0], axis[1], center + axis[2], properties),
        std::make_shared<Face>(axis[2], axis[0], axis[1], center - axis[2], properties)
    };

    _mesh = Mesh(elements);

    std::vector<Point> corners;
    for(const size_t i:{0,1})
        for(const size_t j:{0,1})
            for(const size_t k:{0,1})
                corners.push_back(center + axis[0]*i + axis[1]*j + axis[2]*k);
    
    _bounding_box = BoundingBox::get_BB_by_corners(corners);

    std::array<Vector,3> normalized_axis = {axis[0].normalize(), axis[1].normalize(), axis[2].normalize()};
    std::array<double,3> sizes = {axis[0].norm(), axis[1].norm(), axis[2].norm()};

    _axis = normalized_axis;
    _sizes = sizes;
    _center  = center;
}

BoundingBox Box::get_bounding_box() const
{
    return _bounding_box;
}

bool Box::inside_box(const Point& p) const
{
    for(const size_t i:{0,1,2})
    {
        if(!leD(fabs(_axis[i].dot(p - _center)), _sizes[i]))
            return false;
    }
    return true;
}

bool Box::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    bool intersects = _mesh.intersect_with_ray(r, intersection);
    if(inside_box(r.get_point()))
    {
        intersection.set_is_entering(false);
        intersection.inverse_normal();
    }

    return intersects;
        
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