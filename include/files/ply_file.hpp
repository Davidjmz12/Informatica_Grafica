#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <array>

#include "geometry/triangle.hpp"
#include "geometry/mesh.hpp"

class PlyFile
{
private:
    VectorGeometries _elements;
    std::array<double,6> _bounding_box;

    bool read_header(std::ifstream& file, size_t& num_vertices, size_t& num_faces);

    double standardize(double value, double min, double max) const;

    PlyFile(VectorGeometries elements, std::array<double,6> bounding_box);

public:
    PlyFile(std::string file_path, Property properties);

    VectorGeometries get_elements() const;

    std::array<double,6> get_bounding_box() const;

    PlyFile change_bounding_box(std::array<double,6> new_bounding_box);

    std::shared_ptr<Geometry> to_mesh() const;

    friend std::ostream& operator<<(std::ostream& os, const PlyFile& ply_file);

    std::string to_string() const;

    
};