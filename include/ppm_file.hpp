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
        ColorMap _map;          // Matrix of pixels
        float _maxRange;        // Max value in the file
        float _colorResolution; // Max number of different tones
        int _dimension[2];      // Width and height of the matrix
        std::string format;     // The format identifier
        std::string comments;   // Additional comments in the file

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
        * @brief Apply equalization and clamping to
        *   the image.
        */
        void apply_equalization_clamping();

        /**
        * @brief Apply gamma correction to the image.
        */
        void apply_gamma();

        /**
        * @brief Apply a gamma correction and clamping
        *  to the image
        */
        void apply_gamma_clamping();

        /**
        * @brief Stores the PPM file
        * @param output_file The path in which the file
        *   is going to be stored.
        * @throw std::runtime_error if the file cannot be
        *   open.
        */
        void save(std::string output_file);

};

#endif