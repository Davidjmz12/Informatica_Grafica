
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

Triangle::Triangle(PointWithTexture v0, PointWithTexture v1, PointWithTexture v2, std::shared_ptr<BRDF> brdf)
    : Geometry(brdf)
{
    this->_v0 = v0.point;
    this->_v1 = v1.point;
    this->_v2 = v2.point;
    this->__bb = BoundingBox::get_BB_by_corners({*_v0,*_v1,*_v2});
    if(*_v0 == *_v1 || *_v0 == *_v2 || *_v1 == *_v2)
        throw std::invalid_argument("The vertices of the triangle must be different");
    if(eqD((*_v1-*_v0).cross((*_v2-*_v0)).norm(),0))
        throw std::invalid_argument("All three vertices of the triangle cannot be linearly dependent");
    
    this->_texture_uv = {v0.texture, v1.texture, v2.texture};
}


BoundingBox Triangle::get_bounding_box() const
{
    return this->__bb;
}

std::pair<double, double> Triangle::get_u_v_coordinates(const Point& p) const {

    Point v0 = *_v0;
    Point v1 = *_v1;
    Point v2 = *_v2;

    // Calculate the edge vectors
    Vector v0v1 = v1 - v0;
    Vector v0v2 = v2 - v0;
    Vector v0p = p - v0;


    // Compute the dot products
    double dot00 = v0v1.dot(v0v1);
    double dot01 = v0v1.dot(v0v2);
    double dot11 = v0v2.dot(v0v2);
    double dot02 = v0v1.dot(v0p);
    double dot12 = v0v2.dot(v0p);

    // Compute the barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double v = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double w = (dot00 * dot12 - dot01 * dot02) * invDenom;
    double u = 1 - v - w;

    double u_result = u * (*_texture_uv[0])[0] + v * (*_texture_uv[1])[0] + w * (*_texture_uv[2])[0];
    double v_result = u * (*_texture_uv[0])[1] + v * (*_texture_uv[1])[1] + w * (*_texture_uv[2])[1];
    return std::make_pair(2*u_result-1, 2*v_result-1);
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
    
    intersection.set_u_v(this->get_u_v_coordinates(intersection.get_int_point()));
    
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