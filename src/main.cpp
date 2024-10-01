#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\assets\\in\\forest_path_fake.ppm");
        file.save("..\\..\\assets\\out\\forest_path_fake.ppm");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}