#pragma once

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <array>

#include "geometry/geometry.hpp"
#include "geometry/triangle.hpp"

class PlyFile
{
private:
    std::vector<Geometry*> _elements;
    std::array<double,6> _bounding_box;
    Property _properties;

    bool read_header(std::ifstream& file, size_t& num_vertices, size_t& num_faces);

    double standardize(double value, double min, double max) const;

    PlyFile(std::vector<Geometry*> elements, std::array<double,6> bounding_box, Property properties);

public:
    PlyFile(std::string file_path, Property properties);

    std::vector<Geometry*> get_elements() const;

    std::array<double,6> get_bounding_box() const;

    PlyFile change_bounding_box(std::array<double,6> new_bounding_box);

    std::string to_string() const;
};