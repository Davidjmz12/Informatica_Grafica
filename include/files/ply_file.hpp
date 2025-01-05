#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <array>

#include "geometry/triangle.hpp"
#include "geometry/mesh.hpp"


using VectorTriangles = std::vector<std::shared_ptr<Triangle>>;
using PointsVector = std::vector<PointWithTexture>;
using HashProperties = std::unordered_map<std::string, size_t>;



class PlyFile
{
private:
    VectorTriangles _elements;
    PointsVector _points;
    std::array<double,6> _bounding_box{};

    size_t _num_vertices, _num_faces;
    bool _has_normals = false;
    bool _has_texture = false;
    HashProperties _properties_vertices_map;

    bool read_header(std::ifstream& file);

    bool read_points(std::ifstream& file);

    bool read_faces(std::ifstream& file, std::shared_ptr<BRDF> properties);

    static double standardize(double value, double min, double max) ;

    PlyFile(VectorTriangles elements, const std::array<double,6>& bounding_box);

public:
    PlyFile(const std::string& file_path, std::shared_ptr<BRDF> brdf);

    [[nodiscard]] VectorTriangles get_elements() const;

    [[nodiscard]] std::array<double,6> get_bounding_box() const;

    [[nodiscard]] std::shared_ptr<Geometry> to_mesh() const;

    friend std::ostream& operator<<(std::ostream& os, const PlyFile& ply_file);

    [[nodiscard]] std::string to_string() const;

};