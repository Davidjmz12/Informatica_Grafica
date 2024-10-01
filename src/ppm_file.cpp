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

std::vector<std::vector<Pixel>> PpmFile::readPixelMap(std::ifstream& file, float factor)
{
    std::vector<std::vector<Pixel>> pixels(this->_dimension[1], std::vector<Pixel>(this->_dimension[0],Pixel(0,0,0)));
    float red, green, blue;

    // Read the pixels
    for (int i = 0; i < this->_dimension[1]; i++)
    {
        std::istringstream s(readOneLine(file));

        // Read each pixel of the line
        for (int j = 0; j < this->_dimension[0]; j++)
        {
            s >> red >> green >> blue;
            pixels[i][j] = Pixel(red*factor,green*factor,blue*factor);
        }
    }

    return pixels;
}

PpmFile::PpmFile(std::string path)
{
    std::ifstream file(path);

    // Check if the file can be open
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    this->format = readOneLine(file);

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
    this->_map = PixelMap(readPixelMap(file, this->_maxRange / this->_colorResolution), RGB);
}

void PpmFile::save(std::string output_file)
{
    std::ofstream file(output_file);

    // Check if we can write the file
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Write headers
    file << std::fixed << this->format << std::endl;
    file << "#MAX=" << std::endl;
    file << this->_dimension[0] << " " << this->_dimension[1] << std::endl;
    file << (int)this->_colorResolution << std::endl;
    file << this->_map << std::endl;
}

void PpmFile::apply_clamping()
{
    // ToneMapping clamping = ToneMapping::clamping(1);
    // this->_map.apply_tone_mapping(clamping);
}

void PpmFile::apply_equalization()
{
    // ToneMapping equalization = ToneMapping::equalization(this->_colorResolution);
    // this->_map.apply_tone_mapping(equalization);
}

void PpmFile::apply_equalization_clamping()
{
    // ToneMapping equalization_clamping = ToneMapping::equalization_clamping();
    // this->_map.apply_tone_mapping(equalization_clamping);
}

void PpmFile::apply_gamma()
{
    // this->apply_equalization();
    // ToneMapping gamma = ToneMapping::gamma();
    // this->_map.apply_tone_mapping(gamma);
}

void PpmFile::apply_gamma_clamping()
{
    // this->apply_equalization_clamping();
    // this->apply_gamma();
}