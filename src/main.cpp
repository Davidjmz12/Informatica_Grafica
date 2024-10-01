#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\assets\\in\\seymour_park.ppm");
        file.apply_gamma_clamping(0.5, 4);
        file.change_resolution(255);
        file.save("..\\..\\assets\\out\\seymour_park.ppm");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}