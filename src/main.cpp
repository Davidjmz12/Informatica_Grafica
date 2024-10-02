#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        PpmFile clamping = file.apply_clamping();
        clamping.change_resolution(255);
        clamping.save("..\\..\\assets\\out\\forest_path_clamping.ppm");

        PpmFile equalization = file.apply_equalization();
        equalization.change_resolution(255);
        equalization.save("..\\..\\assets\\out\\forest_path_equalization.ppm");

        PpmFile eq_clamping = file.apply_equalization_clamping(24);
        eq_clamping.change_resolution(255);
        eq_clamping.save("..\\..\\assets\\out\\forest_path_equalization_clamping.ppm");

        PpmFile gamma = file.apply_gamma(0.5); // sqrt(x/8)
        gamma.change_resolution(255);
        gamma.save("..\\..\\assets\\out\\forest_path_gamma.ppm");

        PpmFile gamma_clamping = file.apply_gamma_clamping(0.5,4); // sqrt(x/4) clamped from 4
        gamma_clamping.change_resolution(255);
        gamma_clamping.save("..\\..\\assets\\out\\forest_path_gamma_clamping.ppm");

        PpmFile drago = file.apply_drago();
        drago.change_resolution(255);
        drago.save("..\\..\\assets\\out\\forest_path_drago.ppm");

        PpmFile log = file.apply_logarithmic(5);
        log.change_resolution(255);
        log.save("..\\..\\assets\\out\\forest_path_logarithmic.ppm");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}