#include <iostream>
#include "ppm_file.hpp"

int main()
{
    try {
        PpmFile file = PpmFile("..\\..\\examples\\forest_path.ppm");
        file.save("..\\..\\examples\\output.txt");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}