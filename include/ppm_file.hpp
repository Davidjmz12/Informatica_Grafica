/**
 * @file ppm_file.hpp
 * @brief Defines the class for work with PPM files.
 *
 * This file contains the definition of the PpmFile class, which represents
 * a file in PPM format.
*/

#ifndef PPM_FILE
#define PPM_FILE

#include <string>

#include "color_map.hpp"

/**
 * @brief A class for represents a PPM file.
 */
class PpmFile {
    private:
        ColorMap _map;          // Matrix of colors.
        float _maxRange;        // Max value in the file
        float _colorResolution; // Max number of different tones
        int _dimension[2];      // Width and height of the matrix
        std::string _format;     // The format identifier

        std::vector<std::vector<Color>> readPixelMap(std::ifstream& file);

    public:
        /**
        * @brief The constructor for representing PPM files
        * @param path The path of the PPM file.
        * @throw std::runtime_error if the file cannot be open or if
        *   the file does not have the correct format of PPM files.
        */
        PpmFile(std::string path);

        /**
        * @brief Apply clamping to the image.
        */
        void apply_clamping();

        /**
        * @brief Apply equalization to the image.
        */
        void apply_equalization();

        /**
        * @brief Apply equalization and clamping to the image.
        * @param V The clamping value.
        */
        void apply_equalization_clamping(float V);

        /**
        * @brief Apply gamma correction to the image.
        * @param gamma The gamma correction value.
        */
        void apply_gamma(float gamma);

        /**
        * @brief Apply gamma correction and clamping to the image.
        * @param gamma The gamma correction value.
        * @param V The clamping value.
        */
        void apply_gamma_clamping(float gamma, float V);

        void change_resolution(int resolution);

        /**
        * @brief Stores the PPM file
        * @param output_file The path in which the file
        *   is going to be stored.
        * @throw std::runtime_error if the file cannot be
        *   open.
        */
        void save(std::string output_file) const;

};

#endif