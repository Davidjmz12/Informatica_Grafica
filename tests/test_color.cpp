/**
 * @file test_color.cpp
 * @brief File that tests the Color class
 *
 * This file contains all the tests that have been made
 * for the Color class.
*/

#include "test.hpp"
#include "color.hpp"

int main()
{    
    Tests t = Tests("COLOR TESTS");
    Color p = Color(200,230,210,RGB).RGB_to_HSV();
    std::cout << p.HSV_to_RGB() << std::endl;
    
    return t.runAll();
}