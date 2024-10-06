#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>

#include "geometry/triangle.hpp"

class PlyFile
{
private:
    std::vector<Triangle> _triangles;

    bool read_header(std::ifstream& file, unsigned int& num_vertices, unsigned int& num_faces);

public:
    PlyFile(std::string file_path);

    std::vector<Triangle> get_triangles() const;
};