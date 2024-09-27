#include <fstream>
#include <sstream>
#include <iostream>

#include "ppm_file.hpp"

PpmFile::PpmFile(std::string path)
{
    std::ifstream file(path);
    std::string line;

    // Check if the file can be open
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Read the format
    if (getline(file,line))
        this->format = line;
    else
        throw std::runtime_error("File does not have a correct format.");

    // Read first comment
    if (!getline(file,line))
        throw std::runtime_error("File does not have a correct format.");

    this->_maxRange = 1; // Default
    while (line[0] == '#') {
        if (this->comments == "")
            this->comments = line;
        else
            this->comments = this->comments + "\n" + line;

        if (line.substr(0,5) == "#MAX=")
            this->_maxRange = std::stof(line.substr(5));

        // Next comment
        if (!getline(file,line))
            throw std::runtime_error("File does not have a correct format.");
    }

    // Dimensions
    std::istringstream stream(line);
    stream >> this->_dimension[0] >> this->_dimension[1];

    // Maximum value
    if (!getline(file,line))
        throw std::runtime_error("File does not have a correct format.");

    this->_colorResolution = std::stof(line);

    // Pixel map
    std::vector<std::vector<Pixel>> pixels(this->_dimension[1], std::vector<Pixel>(this->_dimension[0],Pixel(0,0,0)));
    float red, green, blue;
    
    // Read line
    float conversion = this->_maxRange / this->_colorResolution;
    for (int i = 0; i < this->_dimension[1]; i++)
    {
        if (!getline(file,line))
            throw std::runtime_error("File does not have a correct format.");
        std::istringstream s(line);

        // Read each pixel of the line
        for (int j = 0; j < this->_dimension[0]; j++)
        {
            s >> red >> green >> blue;
            pixels[i][j] = Pixel(red*conversion,green*conversion,blue*conversion);
        }
    }

    // Create the Pixel Map
    this->_map = PixelMap(pixels, RGB);
}

void PpmFile::save(std::string output_file)
{
    std::ofstream file(output_file);

    // Check if we can write the file
    if (!file.is_open())
        throw std::runtime_error("The path cannot be open.");

    // Write headers
    file << std::fixed << this->format << std::endl;
    file << this->comments << std::endl;
    file << this->_dimension[0] << " " << this->_dimension[1] << std::endl;
    file << (int)this->_colorResolution << std::endl;
    file << this->_map << std::endl;
}

void PpmFile::apply_clamping()
{
    ToneMapping clamping = ToneMapping::clamping(1);
    this->_map.apply_tone_mapping(clamping);
}

void PpmFile::apply_equalization()
{
    ToneMapping equalization = ToneMapping::equalization(this->_colorResolution);
    this->_map.apply_tone_mapping(equalization);
}

void PpmFile::apply_equalization_clamping()
{
    ToneMapping equalization_clamping = ToneMapping::equalization_clamping();
    this->_map.apply_tone_mapping(equalization_clamping);
}

void PpmFile::apply_gamma()
{
    this->apply_equalization();
    ToneMapping gamma = ToneMapping::gamma();
    this->_map.apply_tone_mapping(gamma);
}

void PpmFile::apply_gamma_clamping()
{
    this->apply_equalization_clamping();
    this->apply_gamma();
}