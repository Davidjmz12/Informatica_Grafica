#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <array>

#include "geometry/triangle.hpp"
#include "geometry/mesh.hpp"

using VectorTriangles = std::vector<std::shared_ptr<Triangle>>;
using PointsVector = std::vector<std::shared_ptr<Point>>;

class PlyFile
{
private:
    VectorTriangles _elements;
    PointsVector _points;
    std::array<double,6> _bounding_box{};

    static bool read_header(std::ifstream& file, size_t& num_vertices, size_t& num_faces);

    static double standardize(double value, double min, double max) ;

    PlyFile(VectorTriangles elements, const std::array<double,6>& bounding_box);

public:
    PlyFile(const std::string& file_path, std::shared_ptr<Property> properties);

    [[nodiscard]] VectorTriangles get_elements() const;

    [[nodiscard]] std::array<double,6> get_bounding_box() const;

    void change_bounding_box(std::array<double,6> new_bounding_box);

    [[nodiscard]] std::shared_ptr<Geometry> to_mesh() const;

    friend std::ostream& operator<<(std::ostream& os, const PlyFile& ply_file);

    [[nodiscard]] std::string to_string() const;

    
};