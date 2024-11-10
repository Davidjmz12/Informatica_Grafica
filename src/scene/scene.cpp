#include "scene/scene.hpp"

Scene::Scene(VectorGeometries objects,  VectorPunctualLight lights, VectorAreaLight area_lights, Camera camera)
    : _objects(objects), _camera(camera), _punctual_lights(lights), _area_lights(area_lights)
{}


std::array<int,2> Scene::get_resolution() const
{
    return this->_camera.get_resolution();
}

bool Scene::intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const
{
    return this->_objects.intersect_with_ray(ray, intersection);
}

VectorPunctualLight Scene::get_punctual_lights() const
{
    return this->_punctual_lights;
}

VectorAreaLight Scene::get_area_lights() const
{
    return this->_area_lights;
}

Camera Scene::get_camera() const
{
    return this->_camera;
}

KDTree& Scene::get_objects()
{
    return this->_objects;
}

std::ostream& operator<<(std::ostream& os, Scene s)
{
    os << s._camera << std::endl;
    os << "Objects:" << std::endl;
    os << s._objects.to_string() << std::endl;
    return os;
}