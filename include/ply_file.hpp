#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <array>

#include "geometry/triangle.hpp"

class PlyFile
{
private:
    std::vector<Triangle> _triangles;
    std::array<double,6> _bounding_box;

    bool read_header(std::ifstream& file, unsigned int& num_vertices, unsigned int& num_faces);

    double standarize(double value, double min, double max) const;

    PlyFile(std::vector<Triangle> triangles, std::array<double,6> bounding_box);

public:
    PlyFile(std::string file_path);

    std::vector<Triangle> get_triangles() const;

    std::array<double,6> get_bounding_box() const;

    PlyFile change_bounding_box(std::array<double,6> new_bounding_box);

    std::string to_string() const;
};