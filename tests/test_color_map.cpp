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
    
    ColorMap c1 = ColorMap({
                            {Color::RGBNormalized(255, 0, 0, 255), Color::RGBNormalized(0, 255, 0, 255), Color::RGBNormalized(0, 0, 255, 255)},
                            {Color::RGBNormalized(255, 255, 0, 255), Color::RGBNormalized(0, 255, 255, 255), Color::RGBNormalized(255, 0, 255, 255)},
                            {Color::RGBNormalized(255, 250, 100, 255), Color::RGBNormalized(30, 255, 100, 255), Color::RGBNormalized(60, 255, 100, 255)},
                           }, RGB);

    ColorMap c2 = ColorMap({
                            {Color(1, 0, 0, RGB), Color(0, 1, 0, RGB), Color(0, 0, 1, RGB)},
                            {Color(1, 1, 0, RGB), Color(0, 1, 1, RGB), Color(1, 0, 1, RGB)},
                            {Color(1, 250/255.0, 100/255.0, RGB), Color(30/255.0, 1, 100/255.0, RGB), Color(60/255.0, 1, 100/255.0, RGB)},
                           }, RGB);


    t.addTest("1", Test::EXPECT_EQ(c1, c1.RGB_to_HSV().HSV_to_RGB()));
    t.addTest("2", Test::EXPECT_EQ(c2, c2.RGB_to_HSV().HSV_to_RGB()));
    t.addTest("3", Test::EXPECT_EQ(c1, c2));

    return t.runAll();
}