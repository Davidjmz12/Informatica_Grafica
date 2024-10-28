#pragma once
#include <string>
#include <unordered_map>

#include "scene/scene.hpp"
#include "geometry/all_geometry.hpp"
#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"

using PropertyHash = std::unordered_map<std::string, Property>;

class SceneFile {
private:
    mutable std::ifstream file;

    Point read_point() const;
    Vector read_vector() const;
    Camera read_camera() const;
    PropertyHash read_properties() const;
    std::vector<Geometry*> read_geometries(PropertyHash ch) const;
    std::vector<Light> read_lights() const;
    ToneMapping* read_tone_mapping() const;
    std::array<int,2> read_resolution() const;
    int read_header(std::string expected) const;
public:
    SceneFile(std::string file);
    void read_scene(std::string file_save) const;
};