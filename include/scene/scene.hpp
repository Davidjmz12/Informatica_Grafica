/**
 * @file scene.hpp
 * @brief Defines a scene.
 * @author David Tizne Ondiviela
 *
 * This file contains the definition of the Scene class,
 * which represents a scene with geometry objects.
*/
#pragma once

#include "light/area_light.hpp"
#include "scene/camera.hpp"
#include "light/area_light.hpp"
#include "light/punctual_light.hpp"
#include "geometry/kd-trees/kd-tree.hpp"

using VectorPunctualLight = std::vector<std::shared_ptr<PunctualLight>>;
using VectorAreaLight = std::vector<std::shared_ptr<AreaLight>>;

/**
 * @brief Class for representing a scene with geometry
 * objects.
 */
class Scene
{
private:
    KDTree _objects; // Vector of objects
    VectorPunctualLight _punctual_lights;      // Vector of lights
    VectorAreaLight _area_lights;
    Camera _camera;                  // Camera

public:
    /**
     * @brief Constructor for the Scene objects.
     * @param objects Vector of Geometry objects in the
     * scene.
     * @param lights Vector of punctual lights in the scene.
     * @param area_lights Vector of area lights in the scene.
     * @param camera Camera on the scene.
     */
    Scene(VectorGeometries objects,  VectorPunctualLight lights, VectorAreaLight area_lights, Camera camera);

    [[nodiscard]] std::array<int,2> get_resolution() const;

    bool intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const;

    [[nodiscard]] VectorPunctualLight get_punctual_lights() const;
    [[nodiscard]] VectorAreaLight get_area_lights() const;
    [[nodiscard]] KDTree& get_objects();
    [[nodiscard]] Camera get_camera() const;

    /**
     * @brief Write the information of the scene.
     * @param os The ostream.
     * @param s The scene.
     */
    friend std::ostream& operator<<(std::ostream& os, Scene s);
};
