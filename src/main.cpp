#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        // PpmFile file = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file.apply_clamping();
        // file.change_resolution(255);
        // file.save("..\\..\\assets\\out\\forest_path_clamping.ppm");

        // PpmFile file2 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file2.apply_equalization();
        // file2.change_resolution(255);
        // file2.save("..\\..\\assets\\out\\forest_path_equalization.ppm");

        // PpmFile file3 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file3.apply_equalization_clamping(24);
        // file3.change_resolution(255);
        // file3.save("..\\..\\assets\\out\\forest_path_equalization_clamping.ppm");

        // PpmFile file4 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file4.apply_gamma(0.5); // sqrt(x/8)
        // file4.change_resolution(255);
        // file4.save("..\\..\\assets\\out\\forest_path_gamma.ppm");

        // PpmFile file5 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file5.apply_gamma_clamping(0.5,4); // sqrt(x/4) clamped from 4
        // file5.change_resolution(255);
        // file5.save("..\\..\\assets\\out\\forest_path_gamma_clamping.ppm");

        
        // PpmFile file6 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        // file6.apply_drago();
        // file6.change_resolution(255);
        // file6.save("..\\..\\assets\\out\\forest_path_drago.ppm");

        PpmFile file7 = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        file7.apply_logarithmic(5);
        file7.change_resolution(255);
        file7.save("..\\..\\assets\\out\\forest_path_logarithmic.ppm");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}