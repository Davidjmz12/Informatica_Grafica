/**
 * @file test_pixel.cpp
 * @brief File that tests the Pixel class
 *
 * This file contains all the tests that have been made
 * for the Pixel class.
*/

#include "test.hpp"
#include "pixel.hpp"

int main()
{    
    Tests t = Tests("PIXEL MAP TESTS");
    Pixel p = Pixel(200,230,210,RGB);
    std::cout << p.RGB_to_HSV()<< std::endl;
    
    return t.runAll();
}