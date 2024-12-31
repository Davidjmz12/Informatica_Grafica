/**
 * @file color_map.hpp
 * @brief Implementation of the PpmFile header.
 * @authors Davidjmz12 DavidTizne
 * @date 01/10/2024
 *
 * This file contains the implementation of the PpmFile class, which represents
 * a file in PPM format.
*/


#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include "files/ppm_file.hpp"

std::string readOneLine(std::ifstream& file)
{
    std::string line;

    if (!getline(file,line))
        throw std::runtime_error("File does not have a correct format.");

    return line;
}

ColorRGB PpmFile::get_color(double x, double y) const
{
    int _x = static_cast<int>(x*(this->_dimension[0]));
    int _y = static_cast<int>(y*(this->_dimension[1]));
    ColorRGB a = this->_map.get_color(_x,_y);
    return a;
}

MatrixRGB PpmFile::readPixelMap(std::ifstream& file) const
{
    MatrixRGB pixels;
    double factor = this->_maxRange/this->_colorResolution;
    double red, green, blue;

    // Read the pixels
    for (int i = 0; i < this->_dimension[1]; i++)
    {
        std::vector<ColorRGB> row;
        std::istringstream s(readOneLine(file));

        // Read each pixel of the line
        for (int j = 0; j < this->_dimension[0]; j++)
        {
            s >> red >> green >> blue;
            row.push_back(ColorRGB(SC3{red*factor,green*factor,blue*factor}));
        }
        pixels.push_back(row);
    }

    return pixels;
}

PpmFile::PpmFile(const std::string& path)
{
    std::ifstream file(path);

    // Check if the file can be open
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    this->_format = readOneLine(file);

    // Read first comment
    std::string comment = readOneLine(file);

    this->_maxRange = 1.0; // Default
    while (comment[0] == '#') {
        if (comment.substr(0,5) == "#MAX=")
            this->_maxRange = std::stof(comment.substr(5));

        // Next comment
        comment = readOneLine(file);
    }

    // Dimensions
    std::istringstream stream(comment);
    stream >> this->_dimension[0] >> this->_dimension[1];

    // Color resolution
    this->_colorResolution = std::stof(readOneLine(file));
    
    // Create the Pixel Map
    this->_map = ColorMap(readPixelMap(file));
}

PpmFile::PpmFile(ColorMap map, const double maxRange, const double colorResolution, const std::array<int,2> dimension, std::string  format)
    : _map(std::move(map)), _maxRange(maxRange), _colorResolution(colorResolution), _dimension{dimension}, _format(std::move(format))
{}

PpmFile PpmFile::apply_tone_mapping(const std::unique_ptr<ToneMapping>& t, const size_t new_resolution) const
{
    return {this->_map.apply_tone_mapping(t, new_resolution),
        this->_maxRange,static_cast<double>(new_resolution),
        this->_dimension,
        this->_format};
}


void PpmFile::save(const std::string& output_file) const
{
    std::ofstream file(output_file);

    // Check if we can write the file
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Write headers
    file << std::fixed << this->_format << std::endl;
    file << "#MAX=" << this->_maxRange << std::endl;
    file << this->_dimension[0] << " " << (int)this->_dimension[1] << std::endl;
    file << static_cast<int>(this->_colorResolution) << std::endl;
    file << this->_map << std::endl;
}


double PpmFile::get_range() const
{
    return this->_maxRange;
}

double PpmFile::get_color_resolution() const
{
    return this->_colorResolution;
}

std::array<int,2> PpmFile::get_dimension() const
{
    return this->_dimension;
}

std::string PpmFile::get_format() const
{
    return this->_format;
}

double PpmFile::get_max_range() const
{
    return this->_maxRange;
}

