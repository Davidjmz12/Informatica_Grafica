/**
 * @file test_color_map.cpp
 * @brief File that tests the ColorMap class
 *
 * This file contains all the tests that have been made
 * for the ColorMap class.
*/

#include "test/test.hpp"
#include "color/color_map.hpp"

int main()
{    
    Tests t = Tests("COLOR MAP TESTS");

    ColorMap c1 = ColorMap({
                            {Color({255, 0, 0}, Color::RGB_255_RANGE, RGB), Color({0, 255, 0}, Color::RGB_255_RANGE, RGB), Color({0, 0, 255},Color::RGB_255_RANGE, RGB)},
                            {Color({255, 255, 0}, Color::RGB_255_RANGE, RGB), Color({0, 255, 255}, Color::RGB_255_RANGE, RGB), Color({255, 0, 255}, Color::RGB_255_RANGE, RGB)},
                            {Color({255, 250, 100}, Color::RGB_255_RANGE, RGB), Color({30, 255, 100}, Color::RGB_255_RANGE, RGB), Color({60, 255, 100}, Color::RGB_255_RANGE, RGB)},
                           }, RGB);

    ColorMap c2 = ColorMap({
                            {Color({1, 0, 0}, Color::RGB_STANDARD_RANGE , RGB), Color({0, 1, 0}, Color::RGB_STANDARD_RANGE, RGB), Color({0, 0, 1}, Color::RGB_STANDARD_RANGE, RGB)},
                            {Color({1, 1, 0}, Color::RGB_STANDARD_RANGE, RGB), Color({0, 1, 1}, Color::RGB_STANDARD_RANGE, RGB), Color({1, 0, 1}, Color::RGB_STANDARD_RANGE, RGB)},
                            {Color({1, 250/255.0, 100/255.0}, Color::RGB_STANDARD_RANGE, RGB), Color({30/255.0, 1, 100/255.0}, Color::RGB_STANDARD_RANGE, RGB), Color({60/255.0, 1, 100/255.0}, Color::RGB_STANDARD_RANGE , RGB)},
                           }, RGB);


    t.addTest("1", Test::EXPECT_EQ(c1.normalize(), c1.RGB_to_HSV().HSV_to_RGB()));
    t.addTest("2", Test::EXPECT_EQ(c2.normalize(), c2.RGB_to_HSV().HSV_to_RGB()));
    t.addTest("3", Test::EXPECT_EQ(c1.normalize(), c2.normalize()));

    return t.runAll();
}