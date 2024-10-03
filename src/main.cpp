#include <iostream>
#include "ply_file.hpp"

int main()
{
    try {
        PlyFile file = PlyFile("../../assets/in/airplane.ply");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}