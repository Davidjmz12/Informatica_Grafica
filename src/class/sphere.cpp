#include "sphere.hpp"
#include "linear_map.hpp"
#include "base.hpp"
#include <math.h>

void imprimir_matriz(float m[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

Sphere::Sphere(Geometric center, Geometric axis, Geometric ref_point)
    : center(center), ref_point(ref_point), axis(axis), radius(axis.norm() / 2)
{
    // Check if the parameters are correct
    if (center.is_vector() || axis.is_point() || ref_point.is_vector())
        throw std::invalid_argument("Center and ref_point must be points. Axis must be a vector.");

    // Check if the ref_point is in the sphere
    if (!this->point_in_sphere(ref_point))
        throw std::invalid_argument("Error: The ref_point is not in the sphere.");
}

Base Sphere::base_point(float inclination, float azimut)
{
    /*
    Linear_Map r1 = Linear_Map(this->axis,azimut);
    Vector axis_second_rotation = r1*this->axis.cross(this->ref_point - this->center);

    imprimir_matriz(r1.matrix);

    float angle_ref_axis = acos(this->axis.normalize().dot((this->ref_point-this->center).normalize()));

    Linear_Map r2 = Linear_Map(axis_second_rotation, inclination - angle_ref_axis);

    Point base_point = r2*r1*this->ref_point;

    return Base(base_point, axis_second_rotation, axis_second_rotation, axis_second_rotation);
    */
   Geometric v = Geometric::vector(1,2,3);
   return Base(v,v,v,v);
}


bool Sphere::point_in_sphere(Geometric p) {
    float radius_point_p = (this->center - p).norm();
    return radius_point_p == this->radius;
}