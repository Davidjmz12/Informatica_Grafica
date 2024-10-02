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
#include "tone_mapping.hpp"

/**
 * @brief A class for represents a PPM file.
 */
class PpmFile {
    private:
        ColorMap _map;          // Matrix of colors.
        float _maxRange;        // Max value in the file
        float _colorResolution; // Max number of different tones
        std::array<int,2> _dimension;      // Width and height of the matrix
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

        PpmFile(ColorMap map, float range, float colorResolution, std::array<int,2> dim, std::string format);

        /**
        * @brief Apply clamping to the image.
        */
        PpmFile apply_clamping();

        /**
        * @brief Apply equalization to the image.
        */
        PpmFile apply_equalization();

        /**
        * @brief Apply equalization and clamping to the image.
        * @param V The clamping value.
        */
        PpmFile apply_equalization_clamping(float V);

        /**
        * @brief Apply gamma correction to the image.
        * @param gamma The gamma correction value.
        */
        PpmFile apply_gamma(float gamma);

        /**
        * @brief Apply gamma correction and clamping to the image.
        * @param gamma The gamma correction value.
        * @param V The clamping value.
        */
        PpmFile apply_gamma_clamping(float gamma, float V);

        /**
         * @brief Apply drago correction to the image.
         */
        PpmFile apply_drago();

        /**
         * @brief Apply logarithmic correction to the image.
         */
        PpmFile apply_logarithmic(float alpha);

        /**
         * @brief Changes the resolution of the image.
         * 
         * This function adjusts the resolution of the image to the specified value.
         * 
         * @param resolution The new resolution to set for the image.
         */
        void change_resolution(int resolution);

        /**
        * @brief Stores the PPM file
        * @param output_file The path in which the file
        *   is going to be stored.
        * @throw std::runtime_error if the file cannot be
        *   open.
        */
        void save(std::string output_file) const;

        float get_range() const;
        float get_color_resolution() const;
        std::array<int,2> get_dimension() const;
        std::string get_format() const;

};

#endif