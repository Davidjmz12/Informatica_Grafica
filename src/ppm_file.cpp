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

#include "ppm_file.hpp"

std::string readOneLine(std::ifstream& file)
{
    std::string line;

    if (!getline(file,line))
        throw std::runtime_error("File does not have a correct format.");

    return line;
}

std::vector<std::vector<Color>> PpmFile::readPixelMap(std::ifstream& file)
{
    std::vector<std::vector<Color>> pixels;
    float factor = this->_maxRange/this->_colorResolution;
    float red, green, blue;

    // Read the pixels
    for (int i = 0; i < this->_dimension[1]; i++)
    {
        std::vector<Color> row;
        std::istringstream s(readOneLine(file));

        // Read each pixel of the line
        for (int j = 0; j < this->_dimension[0]; j++)
        {
            s >> red >> green >> blue;
            row.push_back(Color({red*factor,green*factor,blue*factor},
                                {this->_maxRange, this->_maxRange,this->_maxRange},
                                RGB));
        }
        pixels.push_back(row);
    }

    return pixels;
}

PpmFile::PpmFile(std::string path)
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
    this->_map = ColorMap(readPixelMap(file), RGB);
}

void PpmFile::save(std::string output_file) const
{
    std::ofstream file(output_file);

    // Check if we can write the file
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Write headers
    file << std::fixed << this->_format << std::endl;
    file << "#MAX=" << this->_maxRange << std::endl;
    file << this->_dimension[0] << " " << this->_dimension[1] << std::endl;
    file << (int)this->_colorResolution << std::endl;
    file << this->_map << std::endl;
}

void PpmFile::apply_clamping()
{
    // ToneMapping clamping = ToneMapping::clamping(this->_maxRange);
    ToneMapping* clamping = new Clamping(this->_maxRange);
    this->_map = this->_map.apply_tone_mapping(clamping);
}

void PpmFile::change_resolution(int resolution)
{
    this->_colorResolution = (float)resolution;
    this->_map = this->_map.change_range({(float)resolution, (float)resolution, (float)resolution});
}

void PpmFile::apply_equalization()
{
    ToneMapping* equalization = new Equalization(this->_maxRange);
    this->_map = this->_map.apply_tone_mapping(equalization);
}

void PpmFile::apply_equalization_clamping(float V)
{
    ToneMapping* equalization_clamping = new EqualizationClamping(V, this->_maxRange);
    this->_map = this->_map.apply_tone_mapping(equalization_clamping);
}

void PpmFile::apply_gamma(float gamma)
{
    ToneMapping* _gamma = new Gamma(gamma, this->_maxRange);
    this->_map = this->_map.apply_tone_mapping(_gamma);
}

void PpmFile::apply_gamma_clamping(float gamma, float V)
{
    ToneMapping* _gamma_clamping = new GammaClamping(gamma, V, this->_maxRange);
    this->_map = this->_map.apply_tone_mapping(_gamma_clamping);
}