#pragma once
#include <string>
#include <unordered_map>
#include <regex>


#include "scene/scene.hpp"
#include "geometry/all_geometry.hpp"
#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"

using PropertyHash = std::unordered_map<std::string, Property>;

class SceneFile {
private:
    std::string read_line() const;

    std::string _ply_dir;
    mutable std::ifstream _file;

    Point read_point() const;
    Vector read_vector() const;
    Camera read_camera() const;
    PropertyHash read_properties() const;
    std::vector<Geometry*> read_geometries(PropertyHash ch) const;
    std::vector<Light> read_lights() const;
    ToneMapping* read_tone_mapping(double max) const;
    std::array<int,2> read_resolution() const;
    int read_header(std::string expected) const;
    SpectralColor read_color() const;
    BRDF* read_brdf(SpectralColor c) const;
    std::array<double,6> read_bounding_box() const;



    Geometry* read_plane(PropertyHash ch) const;
    Geometry* read_sphere(PropertyHash ch) const;
    Geometry* read_cylinder(PropertyHash ch) const;
    Geometry* read_mesh(PropertyHash ch) const;

    ToneMapping* read_gamma_tm(double max) const;

public:
    SceneFile(std::string file, std::string ply_dir);
    void read_scene(std::string file_save) const;
};