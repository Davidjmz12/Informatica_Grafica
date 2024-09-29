/**
 * @file test_color_map.cpp
 * @brief File that tests the ColorMap class
 *
 * This file contains all the tests that have been made
 * for the ColorMap class.
*/

#include "test.hpp"
#include "color_map.hpp"

int main()
{    
    Tests t = Tests("COLOR MAP TESTS");
    
    ColorMap C = ColorMap({{Color(255, 0, 0, 255), Color(0, 255, 0, 255), Color(0, 0, 255, 255)},
                           {Color(255, 0, 0, 255), Color(0, 255, 0, 255), Color(0, 0, 255, 255)}
                           }, RGB);
    std::cout << C << std::endl;
    return t.runAll();
}