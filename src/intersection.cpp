#include "intersection.hpp"

Intersection::Intersection()
{}

Intersection::Intersection(float distance, Geometric normal, Geometric point):
    _distance(distance),_normal(normal),_point(point){}

bool Intersection::operator=(Intersection i) const
{
    return  eqFloat(this->_distance,i._distance) &&
            this->_normal == i._normal &&
            this->_point == i._point;
}