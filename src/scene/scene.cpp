#include "scene/scene.hpp"

Scene::Scene(std::vector<Geometry*> objects,  std::vector<PunctualLight*> lights, std::vector<AreaLight*> area_lights, Camera camera)
    : _objects(objects), _camera(camera), _punctual_lights(lights), _area_lights(area_lights)
{}

void Scene::add_geometry(Geometry* g)
{
    this->_objects.push_back(g);
}

void Scene::add_light(PunctualLight* l)
{
    this->_punctual_lights.push_back(l);
}

std::array<int,2> Scene::get_resolution() const
{
    return this->_camera.get_resolution();
}

std::vector<Geometry*> Scene::get_objects() const
{
    return this->_objects;
}

std::vector<PunctualLight*> Scene::get_punctual_lights() const
{
    return this->_punctual_lights;
}

std::vector<AreaLight*> Scene::get_area_lights() const
{
    return this->_area_lights;
}

Camera Scene::get_camera() const
{
    return this->_camera;
}

std::ostream& operator<<(std::ostream& os, Scene s)
{
    os << s._camera << std::endl;
    os << "Objects:" << std::endl;

    for (auto g : s._objects)
        os << "\t" << g << std::endl;

    return os;
}