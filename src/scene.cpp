#include "scene.hpp"

Scene::Scene(std::vector<Geometry*> objects, Camera camera)
    : _objects(objects), _camera(camera)
{}

void Scene::add_geometry(Geometry* g)
{
    this->_objects.push_back(g);
}

ColorMap Scene::paint_scene()
{
    return ColorMap();
}

std::ostream& operator<<(std::ostream& os, Scene s)
{
    os << s._camera << std::endl;
    os << "Objects:" << std::endl;

    for (auto g : s._objects)
        os << "\t" << g << std::endl;

    return os;
}