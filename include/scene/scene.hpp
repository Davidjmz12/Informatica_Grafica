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
#include "light/area_light/area_light.hpp"
#include "light/light.hpp"


/**
 * @brief Class for representing a scene with geometry
 * objects.
 */
class Scene
{
private:
    std::vector<Geometry*> _objects; // Vector of objects
    std::vector<PunctualLight*> _punctual_lights;      // Vector of lights
    std::vector<AreaLight*> _area_lights;
    Camera _camera;                  // Camera

public:
    /**
     * @brief Constructor for the Scene objects.
     * @param objects Vector of Geometry objects in the
     * scene.
     * @param camera Camera on the scene.
     */
    Scene(std::vector<Geometry*> objects,  std::vector<PunctualLight*> lights, std::vector<AreaLight*> area_lights, Camera camera);

    /**
     * @brief Add a Geometry object to the scene.
     * @param g The geomtry to add.
     */
    void add_geometry(Geometry* g);

    void add_light(PunctualLight* l);

    std::array<int,2> get_resolution() const;

    std::vector<Geometry*> get_objects() const;
    std::vector<PunctualLight*> get_punctual_lights() const;
    std::vector<AreaLight*> get_area_lights() const;
    Camera get_camera() const;

    /**
     * @brief Write the information of the scene.
     * @param os The ostream.
     * @param s The scene.
     */
    friend std::ostream& operator<<(std::ostream& os, Scene s);
};
