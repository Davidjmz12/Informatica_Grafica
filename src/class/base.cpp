#include "base.hpp"

Base::Base(Geometric p, Geometric i, Geometric j, Geometric k)
    : center(p), x(i), y(j), z(k)
{ 
    if (p.is_vector() || i.is_point() || j.is_point() || k.is_point())
        throw std::invalid_argument("p must be a point and i,j,k must be vectors.");

    if (!i.is_base(j,k))
        throw std::invalid_argument("Vectors must be linearly independent.");
    
    float aux[4][4] = { {i[0], j[0], k[0], p[0]},
                        {i[1], j[1], k[1], p[1]},
                        {i[2], j[2], k[2], p[2]},
                        {0   , 0   , 0   , 1   }};

    this->matrix = Matrix4x4(aux);
}


Linear_Map Base::matrix_lt() const
{
    return Linear_Map(this->matrix);
}
        
Geometric Base::point(float x, float y, float z) const
{
    return this->x*x + this->y*y + this->z*z;
}

Base canonic_base(){
    return Base(Geometric::point(0,0,0), 
                Geometric::vector(1,0,0),
                Geometric::vector(0,1,0),
                Geometric::vector(0,0,1));
}

std::ostream& operator<<(std::ostream& os, const Base& b)
{
    os << "Point: " << b.center << "\nBase: " << b.x << " ; " << b.y << " ; " << b.z << std::endl; 
    return os;
}

bool Base::operator==(Base b)
{
    return (this->matrix == b.matrix);
}