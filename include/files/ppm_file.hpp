/**
 * @file ppm_file.hpp
 * @brief Defines the class for work with PPM files.
 *
 * This file contains the definition of the PpmFile class, which represents
 * a file in PPM format.
*/

#pragma once

#include <string>

#include "color/color_map.hpp"
#include "color/tone_mapping/tone_mapping.hpp"
#include "scene.hpp"



/**
 * @brief A class for represents a PPM file.
 */
class PpmFile {
    private:
        ColorMap _map;          // Matrix of colors.
        double _maxRange;        // Max value in the file
        double _colorResolution; // Max number of different tones
        std::array<int,2> _dimension;      // Width and height of the matrix
        std::string _format;     // The format identifier

        MatrixRGB readPixelMap(std::ifstream& file);

    public:
        /**
        * @brief The constructor for representing PPM files
        * @param path The path of the PPM file.
        * @throw std::runtime_error if the file cannot be open or if
        *   the file does not have the correct format of PPM files.
        */
        PpmFile(std::string path);

        PpmFile(ColorMap map, double range, double colorResolution, std::array<int,2> dim, std::string format);

        PpmFile(Scene s);

        PpmFile apply_tone_mapping(ToneMapping* t) const;

        /**
        * @brief Stores the PPM file
        * @param output_file The path in which the file
        *   is going to be stored.
        * @throw std::runtime_error if the file cannot be
        *   open.
        */
        void save(std::string output_file) const;

        double get_range() const;
        double get_color_resolution() const;
        std::array<int,2> get_dimension() const;
        std::string get_format() const;

};

