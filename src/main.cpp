#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\assets\\in\\forest_path.ppm");
        file.apply_clamping();
        file.change_resolution(255);
        file.save("..\\..\\assets\\out\\forest_path.ppm");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}