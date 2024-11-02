#pragma once
#include <string>
#include <unordered_map>
#include <regex>


#include "scene/render.hpp"
#include "geometry/all_geometry.hpp"
#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"
#include "light/area_light/area_light.hpp"

using PropertyHash = std::unordered_map<std::string, Property>;

class SceneFile {
private:
    std::string read_line() const;

    std::string _ply_dir;
    mutable std::ifstream _file;
    PropertyHash _ch;

    Point read_point() const;
    Vector read_vector() const;
    Camera read_camera() const;
    void read_properties();
    std::vector<Geometry*> read_geometries() const;
    void read_lights(std::vector<PunctualLight*>& pl, std::vector<AreaLight*>& al) const;
    ToneMapping* read_tone_mapping(double max) const;
    std::array<int,2> read_resolution() const;
    int read_header(std::string expected) const;
    SpectralColor read_color() const;
    BRDF* read_brdf(SpectralColor c) const;
    std::array<double,6> read_bounding_box() const;

    Property read_property(std::string key) const;


    PunctualLight* read_punctual_light() const;
    AreaLight* read_box_light() const;
    AreaLight* read_sphere_light() const;
    AreaLight* read_plane_light() const;

    Geometry* read_plane(Property p) const;
    Geometry* read_sphere(Property p) const;
    Geometry* read_cylinder(Property p) const;
    Geometry* read_mesh(Property p) const;
    Geometry* read_box(Property p) const;
    Geometry* read_face(Property p) const;
    Geometry* read_cone(Property p) const;
    Geometry* read_disk(Property p) const;	
    Geometry* read_ellipsoid(Property p) const;
    Geometry* read_triangle(Property p) const;


    ToneMapping* read_gamma_tm(double max) const;

public:
    SceneFile(std::string file, std::string ply_dir);
    void read_scene(std::string path, std::string file_save);
};