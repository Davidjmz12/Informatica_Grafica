#ifndef PPM_FILE
#define PPM_FILE

#include <string>

#include "pixel_map.hpp"

class PpmFile {
    private:
        PixelMap _map;
        float _maxRange;
        int _dimension[2];
        std::string format;
        std::string comments;

    public:

        PpmFile(std::string path);

        void apply_clamping();
        void apply_equalization();
        void apply_equalization_clamping();
        void apply_gamma();
        void apply_gamma_clamping();

        void save(std::string output_file);

};

#endif