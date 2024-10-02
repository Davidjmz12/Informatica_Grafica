#include <iostream>
#include "tiff_file.hpp"

int main()
{
    try {
        TiffFile tf("..\\..\\assets\\in\\body3.tif");

    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}