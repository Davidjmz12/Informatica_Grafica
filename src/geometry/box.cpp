#include "geometry/box.hpp"

Box::Box(Point center, std::array<double,3> sides, std::array<Vector,3> axis)
{
    if(sides[0]<=0 || sides[1]<=0 || sides[2]<=0)
        throw std::invalid_argument("The sides of the box must be positive");
    if(neqD(axis[0].norm(),1) || neqD(axis[1].norm(),1) || neqD(axis[2].norm(),1))
        throw std::invalid_argument("The axis of the box must be normalized.");
    if(!axis[0].is_base(axis[1],axis[2]))
        throw std::invalid_argument("The axis of the box must be a R^3 base.");
    
    std::vector<Triangle> triangles;

    // Calculate the half-sizes
    double halfX = sides[0] / 2.0f;
    double halfY = sides[1] / 2.0f;
    double halfZ = sides[2] / 2.0f;

    // Calculate the vertices of the box
    std::array<Point, 8> vertices = {
        center + axis[0] * halfX + axis[1] * halfY + axis[2] * halfZ,
        center + axis[0] * halfX + axis[1] * halfY - axis[2] * halfZ,
        center + axis[0] * halfX - axis[1] * halfY + axis[2] * halfZ,
        center + axis[0] * halfX - axis[1] * halfY - axis[2] * halfZ,
        center - axis[0] * halfX + axis[1] * halfY + axis[2] * halfZ,
        center - axis[0] * halfX + axis[1] * halfY - axis[2] * halfZ,
        center - axis[0] * halfX - axis[1] * halfY + axis[2] * halfZ,
        center - axis[0] * halfX - axis[1] * halfY - axis[2] * halfZ
    };

    // Define the 12 triangles (2 per face)
    triangles = {
        // Front face
        Triangle(vertices[0], vertices[1], vertices[2]),
        Triangle(vertices[1], vertices[3], vertices[2]),
        // Back face
        Triangle(vertices[4], vertices[6], vertices[5]),
        Triangle(vertices[5], vertices[6], vertices[7]),
        // Top face
        Triangle(vertices[0], vertices[4], vertices[1]),
        Triangle(vertices[1], vertices[4], vertices[5]),
        // Bottom face
        Triangle(vertices[2], vertices[3], vertices[6]),
        Triangle(vertices[3], vertices[7], vertices[6]),
        // Left face
        Triangle(vertices[0], vertices[2], vertices[4]),
        Triangle(vertices[2], vertices[6], vertices[4]),
        // Right face
        Triangle(vertices[1], vertices[5], vertices[3]),
        Triangle(vertices[3], vertices[5], vertices[7])
    };

    // Create the TriangleMesh
    _mesh = TriangleMesh(triangles);
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