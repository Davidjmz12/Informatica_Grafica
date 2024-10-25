/**
 * @file test_tone_mapping.cpp
 * @brief File that tests the ToneMapping class
 *
 * This file contains all the tests made
 * for the ToneMapping class.
*/

#include "test/test.hpp"
#include "color/tone_mapping/all_tone_mapping.hpp"


int main()
{    
    Tests t = Tests("TONE MAPPING TESTS");

    // Test constructor
    t.addTest("1",Test::EXPECT_EXC([](){Clamping(0);})); // LMax <= 0
    t.addTest("2",Test::EXPECT_EXC([](){Gamma(-1,1);})); // gamma <= 0
    t.addTest("3",Test::EXPECT_EXC([](){Equalization(1,0.5);})); // V > LMax

    // Tests clamping
    t.addTest("4",Test::EXPECT_EQ(Clamping(2).evaluate(0.5),0.5F));
    t.addTest("5",Test::EXPECT_EQ(Clamping(2).evaluate(1),1.0F));
    t.addTest("6",Test::EXPECT_EQ(Clamping(2).evaluate(2),1.0F));
    t.addTest("7",Test::EXPECT_EQ(Clamping(2).evaluate(1.5),1.0F));

    // Tests equalization
    t.addTest("8",Test::EXPECT_EQ(Equalization(1).evaluate(0.5),0.5F));
    t.addTest("9",Test::EXPECT_EQ(Equalization(2).evaluate(2),1.0F));
    t.addTest("10",Test::EXPECT_EQ(Equalization(10).evaluate(1),0.1F));

    // Tests equalization_clamping
    t.addTest("11",Test::EXPECT_EQ(Equalization(1,2).evaluate(0.5),0.5F));
    t.addTest("12",Test::EXPECT_EQ(Equalization(1,2).evaluate(1.1),1.0F));
    t.addTest("13",Test::EXPECT_EQ(Equalization(5,10).evaluate(0.5),0.1F));
    t.addTest("14",Test::EXPECT_EQ(Equalization(7,10).evaluate(7),1.0F));


    // Tests gamma
    t.addTest("15",Test::EXPECT_EQ(Gamma(1,2).evaluate(2),1.0F));
    t.addTest("16",Test::EXPECT_EQ(Gamma(2,2).evaluate(1),0.25F));
    t.addTest("17",Test::EXPECT_EQ(Gamma(3,10).evaluate(5),1/8.0F));
    t.addTest("18",Test::EXPECT_EQ(Gamma(5,10).evaluate(10),1.0F));
    t.addTest("19",Test::EXPECT_EQ(Gamma(5,10).evaluate(9),(double)pow(9/10.0F,5)));

    // Test gama_clamping
    t.addTest("20",Test::EXPECT_EQ(Gamma(1,1,10).evaluate(2),1.0F));
    t.addTest("21",Test::EXPECT_EQ(Gamma(2,10,10).evaluate(1),0.01F));
    t.addTest("22",Test::EXPECT_EQ(Gamma(3,1,10).evaluate(0.5),1/8.0F));
    t.addTest("23",Test::EXPECT_EQ(Gamma(4,5,10).evaluate(2.5),1/16.0F));
    t.addTest("24",Test::EXPECT_EQ(Gamma(0.5,2,10).evaluate(0.5),1/2.0F));
    t.addTest("25",Test::EXPECT_EQ(Gamma(0.25,0.5,10).evaluate(0.5/16),1/2.0F));


    // Tests evaluate method
    t.addTest("26",Test::EXPECT_EXC([](){Clamping(1).evaluate(1.1);}));
    t.addTest("27",Test::EXPECT_EXC([](){Clamping(1).evaluate(-0.1);}));    

    return t.runAll();
}