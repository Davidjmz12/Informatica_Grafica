#include <fstream>
#include <sstream>

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

    while (line[0] == '#') {
        this->comments = this->comments + '\n' + line;

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

    this->_maxRange = std::stoi(line);

    // Pixel map
    std::vector<std::vector<Pixel>> pixels(this->_dimension[0], std::vector<Pixel>(this->_dimension[1],Pixel(0,0,0)));
    int red, green, blue;
    
    // Read line
    for (int i = 0; i < this->_dimension[0]; i++)
    {
        if (!getline(file,line))
            throw std::runtime_error("File does not have a correct format.");
        std::istringstream s(line);

        // Read each pixel of the line
        for (int j = 0; j < this->_dimension[1]; j++)
        {
            s >> red >> green >> blue;
            pixels[i][j] = Pixel(red,green,blue);
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
    file << this->format << std::endl;
    file << this->comments << std::endl;
    file << this->_dimension[0] + " " + this->_dimension[1] << std::endl;
    file << this->_maxRange << std::endl;
    file << this->_map << std::endl;
}
