/**
 * @file scene.hpp
 * @brief Defines a scene.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the Scene class,
 * which represents a scene with geometry objects.
*/
#pragma once

#include "scene/camera.hpp"
#include "scene/light.hpp"

/**
 * @brief Class for representing a scene with geometry
 * objects.
 */
class Scene
{
private:
    std::vector<Geometry*> _objects; // Vector of objects
    std::vector<Light> _lights;      // Vector of lights
    Camera _camera;                  // Camera

public:
    /**
     * @brief Constructor for the Scene objects.
     * @param objects Vector of Geometry objects in the
     * scene.
     * @param camera Camera on the scene.
     */
    Scene(std::vector<Geometry*> objects,  std::vector<Light> lights, Camera camera);

    /**
     * @brief Add a Geometry object to the scene.
     * @param g The geomtry to add.
     */
    void add_geometry(Geometry* g);

    void add_light(Light l);

    std::array<int,2> get_resolution() const;

    std::vector<Geometry*> get_objects() const;
    std::vector<Light> get_lights() const;
    Camera get_camera() const;

    /**
     * @brief Write the information of the scene.
     * @param os The ostream.
     * @param s The scene.
     */
    friend std::ostream& operator<<(std::ostream& os, Scene s);
};
