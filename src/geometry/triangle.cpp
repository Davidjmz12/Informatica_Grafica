
#include <utility>

#include "geometry/triangle.hpp"

Triangle::Triangle(std::shared_ptr<Point> v0, std::shared_ptr<Point> v1, std::shared_ptr<Point> v2, std::shared_ptr<BRDF> brdf)
    : Geometry(brdf), _v0(std::move(v0)), _v1(std::move(v1)), _v2(std::move(v2))
{
    this->__bb = BoundingBox::get_BB_by_corners({*_v0,*_v1,*_v2});
    if(*_v0 == *_v1 || *_v0 == *_v2 || *_v1 == *_v2)
        throw std::invalid_argument("The vertices of the triangle must be different");
    if(eqD((*_v1-*_v0).cross((*_v2-*_v0)).norm(),0))
        throw std::invalid_argument("All three vertices of the triangle cannot be linearly dependent");
}


BoundingBox Triangle::get_bounding_box() const
{
    return this->__bb;
}


bool Triangle::intersect_with_ray(const Ray& r, IntersectionObject& intersection) const
{
    const Vector v0v1 = *_v1 - *_v0;
    const Vector v0v2 = *_v2 - *_v0;
    const Vector pvec = r.get_direction().cross(v0v2);

    const double det = v0v1.dot(pvec);

    // If the determinant is close to 0, the ray is parallel to the triangle plane
    if (eqD(det, 0))
        return false;

    const double inv_det = 1.0 / det;
    const Vector tvec = r.get_point() - *_v0;

    // Calculate barycentric coordinate u
    const double u = tvec.dot(pvec) * inv_det;
    if (u < 0 || u > 1)
        return false;

    const Vector qvec = tvec.cross(v0v1);

    // Calculate barycentric coordinate v
    const double v = r.get_direction().dot(qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return false;

    // Calculate distance along the ray
    const double t = v0v2.dot(qvec) * inv_det;
    if (t < 0) // Intersection is behind the ray origin
        return false;

    intersection = IntersectionObject(t, v0v1.cross(v0v2).normalize(), r.get_point() + r.get_direction() * t, *this->_brdf, r);
    return true;
}

Point Triangle::operator[](const int i) const
{
    if(i == 0)
        return *this->_v0;
    if(i == 1)
        return *this->_v1;
    if(i == 2)
        return *this->_v2;

    throw std::invalid_argument("Index out of bounds");
}

std::ostream& operator<<(std::ostream& os, const Triangle& t)
{
    os << t.to_string();
    return os;
}

std::string Triangle::to_string() const
{
    return "Triangle: " + this->_v0->to_string() + " " + this->_v1->to_string() + " " + this->_v2->to_string();
}