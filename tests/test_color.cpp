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
    // Test cases for RGB to HSV and vice versa
    Color rgb1 = Color({255, 0, 0}, Color::RGB_255_RANGE, RGB);
    Color hsv1 = rgb1.RGB_to_HSV();
    Color rgb1_converted = hsv1.HSV_to_RGB();
    t.addTest("1", Test::EXPECT_EQ(rgb1, rgb1_converted));

    Color rgb2 = Color({0, 255, 0}, Color::RGB_255_RANGE, RGB);
    Color hsv2 = rgb2.RGB_to_HSV();
    Color rgb2_converted = hsv2.HSV_to_RGB();
    t.addTest("2", Test::EXPECT_EQ(rgb2, rgb2_converted));

    Color rgb3 = Color({0, 0, 255}, Color::RGB_255_RANGE, RGB);
    Color hsv3 = rgb3.RGB_to_HSV();
    Color rgb3_converted = hsv3.HSV_to_RGB();
    t.addTest("3", Test::EXPECT_EQ(rgb3, rgb3_converted));

    Color rgb4 = Color({255, 255, 0}, Color::RGB_255_RANGE, RGB);
    Color hsv4 = rgb4.RGB_to_HSV();
    Color rgb4_converted = hsv4.HSV_to_RGB();
    t.addTest("4", Test::EXPECT_EQ(rgb4, rgb4_converted));

    Color rgb5 = Color({0, 255, 255}, Color::RGB_255_RANGE, RGB);
    Color hsv5 = rgb5.RGB_to_HSV();
    Color rgb5_converted = hsv5.HSV_to_RGB();
    t.addTest("5", Test::EXPECT_EQ(rgb5, rgb5_converted));

    Color rgb6 = Color({255, 0, 255}, Color::RGB_255_RANGE, RGB);
    Color hsv6 = rgb6.RGB_to_HSV();
    Color rgb6_converted = hsv6.HSV_to_RGB();
    t.addTest("6", Test::EXPECT_EQ(rgb6, rgb6_converted));

    Color rgb7 = Color({192, 192, 192}, Color::RGB_255_RANGE, RGB);
    Color hsv7 = rgb7.RGB_to_HSV();
    Color rgb7_converted = hsv7.HSV_to_RGB();
    t.addTest("7", Test::EXPECT_EQ(rgb7, rgb7_converted));

    Color rgb8 = Color({128, 150, 20}, Color::RGB_255_RANGE, RGB);
    Color hsv8 = rgb8.RGB_to_HSV();
    Color rgb8_converted = hsv8.HSV_to_RGB();
    t.addTest("8", Test::EXPECT_EQ(rgb8, rgb8_converted));

    Color rgb9 = Color({128, 139, 100}, Color::RGB_255_RANGE, RGB);
    Color hsv9 = rgb9.RGB_to_HSV();
    Color rgb9_converted = hsv9.HSV_to_RGB();
    t.addTest("9", Test::EXPECT_EQ(rgb9, rgb9_converted));

    Color rgb10 = Color({128, 138, 100}, Color::RGB_255_RANGE, RGB);
    Color hsv10 = rgb10.RGB_to_HSV();
    Color rgb10_converted = hsv10.HSV_to_RGB();
    t.addTest("10", Test::EXPECT_EQ(rgb10, rgb10_converted));


    // Test cases for inequality
    t.addTest("11", Test::EXPECT_NEQ(rgb1, rgb2));
    t.addTest("12", Test::EXPECT_NEQ(rgb1, rgb3));
    t.addTest("13", Test::EXPECT_NEQ(rgb9_converted, rgb10_converted));

    // Test cases for exceptions


    // Test cases for apply_tone_mapping
    Color hsv11 = Color({0, 0, 0.5}, Color::HSV_STANDARD_RANGE, HSV);
    ToneMapping *t1 = new Clamping(1);
    ToneMapping *t2 = new EqualizationClamping(0.5,1);
    ToneMapping *t3 = new GammaClamping(0.5,1,1);
    ToneMapping *t4 = new GammaClamping(2,0.5,1);
    ToneMapping *t5 = new GammaClamping(2,1,1);

    Color hsv11_tone_mapped_1 = hsv11.apply_tone_mapping(t1);
    Color hsv11_tone_mapped_2 = hsv11.apply_tone_mapping(t2);
    Color hsv11_tone_mapped_3 = hsv11.apply_tone_mapping(t3);
    Color hsv11_tone_mapped_4 = hsv11.apply_tone_mapping(t4);
    Color hsv11_tone_mapped_5 = hsv11.apply_tone_mapping(t5);

    t.addTest("14", Test::EXPECT_EQ(hsv11_tone_mapped_1, hsv11));
    t.addTest("15", Test::EXPECT_EQ(hsv11_tone_mapped_2, Color({0,0,1},Color::HSV_STANDARD_RANGE, HSV)));
    t.addTest("16", Test::EXPECT_NEQ(hsv11_tone_mapped_2, hsv11));
    t.addTest("17", Test::EXPECT_EQ(hsv11_tone_mapped_3, Color({0,0,(float)sqrt(0.5)}, Color::HSV_STANDARD_RANGE, HSV)));
    t.addTest("18", Test::EXPECT_EQ(hsv11_tone_mapped_4, Color({0,0,1}, Color::HSV_STANDARD_RANGE, HSV)));
    t.addTest("19", Test::EXPECT_EQ(hsv11_tone_mapped_5, Color({0,0,0.25}, Color::HSV_STANDARD_RANGE, HSV)));
    t.addTest("20", Test::EXPECT_NEQ(hsv11_tone_mapped_5, Color({0,0,0.255}, Color::HSV_STANDARD_RANGE, HSV)));
    


    return t.runAll();
}