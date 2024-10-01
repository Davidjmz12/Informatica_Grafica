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

void PpmFile::save(std::string output_file)
{
    std::ofstream file(output_file);

    // Check if we can write the file
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Write headers
    file << std::fixed << this->_format << std::endl;
    file << "#MAX=" << std::endl;
    file << this->_dimension[0] << " " << this->_dimension[1] << std::endl;
    file << (int)this->_colorResolution << std::endl;
    file << this->_map.change_range({255, 255, 255});
}

void PpmFile::apply_clamping()
{
    ToneMapping clamping = ToneMapping::clamping(this->_colorResolution);
    
}

void PpmFile::apply_equalization()
{
    ToneMapping equalization = ToneMapping::equalization(this->_colorResolution);
}

void PpmFile::apply_equalization_clamping(float V)
{
    ToneMapping equalization_clamping = ToneMapping::equalization_clamping(V, this->_colorResolution);
}

void PpmFile::apply_gamma(float gamma)
{
    ToneMapping _gamma = ToneMapping::gamma(gamma, this->_colorResolution);
}

void PpmFile::apply_gamma_clamping(float gamma, float V)
{
    ToneMapping _gamma_clamping = ToneMapping::gamma_clamping(gamma, V, this->_colorResolution);
}