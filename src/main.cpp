#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file.apply_clamping();
        file.change_resolution(255);
        file.save("..\\..\\assets\\out\\seymour_park_clamping.ppm");

        PpmFile file2 = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file2.apply_equalization();
        file2.change_resolution(255);
        file2.save("..\\..\\assets\\out\\seymour_park_equa.ppm");

        PpmFile file3 = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file3.apply_equalization_clamping(4);
        file3.change_resolution(255);
        file3.save("..\\..\\assets\\out\\seymour_park_eq_clamp.ppm");

        PpmFile file4 = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file4.apply_gamma(0.5); // sqrt(x/8)
        file4.change_resolution(255);
        file4.save("..\\..\\assets\\out\\seymour_park_gamma.ppm");

        PpmFile file5 = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file5.apply_gamma_clamping(0.5,4); // sqrt(x/4) clamped from 4
        file5.change_resolution(255);
        file5.save("..\\..\\assets\\out\\seymour_park_gamma_cla.ppm");

    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}