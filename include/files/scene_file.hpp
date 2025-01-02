/**
 * @file scene_file.hpp
 * @brief This file contains the definition of SceneFile class, which
 *  represents a scene.
 * @authors Davidjmz12 DavidTizne
 * @date 03/11/2024
*/
#pragma once
#include <string>
#include <unordered_map>

#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "light/area_light/area_light.hpp"
#include "kernel_density/all_kernel_densities.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"
#include "files/parse_xml.hpp"

#include "render/ray_tracing.hpp"
#include "render/photon_mapping/direct_photon_mapping.hpp"
#include "render/photon_mapping/explicit_photon_mapping.hpp"

#include "files/parse_xml.hpp"

using BRDFHash = std::unordered_map<std::string, std::shared_ptr<BRDF>>;

/**
 * Class for represent a scene
 */
class SceneFile {

public:
    /**
     * @brief Constructor of the SceneFile class
     * @param file The scene file
     * @param ply_dir The path to the dir with the ply files
     */
    SceneFile(const std::string& file, std::string ply_dir);

    /**
     * @brief Method for reading the file and create the image
     * @param path The path to the directory in which the image
     *  is going to be stored
     */
    void read_scene(const std::string& path);

private:

    std::string _ply_dir;
    XmlNode _root;
    BRDFHash _ch;

    Camera read_camera() const;
    BRDFHash read_properties() const;
    VectorGeometries read_geometries() const;
    VectorPunctualLight read_punctual_lights() const;
    VectorAreaLight read_area_lights() const;
    Render* read_render_type(Scene& s) const;
    std::unique_ptr<ToneMapping> read_tone_mapping(double max) const;

};
