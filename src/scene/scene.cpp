#include "scene/scene.hpp"

Scene::Scene(std::vector<Geometry*> objects,  std::vector<Light> lights, Camera camera)
    : _objects(objects), _camera(camera), _lights(lights)
{}

void Scene::add_geometry(Geometry* g)
{
    this->_objects.push_back(g);
}

void Scene::add_light(Light l)
{
    this->_lights.push_back(l);
}

ColorMap Scene::paint_scene() const
{
    return this->_camera.paint_scene(this->_objects, this->_lights);
}

std::array<int,2> Scene::get_resolution() const
{
    return this->_camera.get_resolution();
}

std::ostream& operator<<(std::ostream& os, Scene s)
{
    os << s._camera << std::endl;
    os << "Objects:" << std::endl;

    for (auto g : s._objects)
        os << "\t" << g << std::endl;

    return os;
}