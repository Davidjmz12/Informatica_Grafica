/**
 * @file test_tone_mapping.cpp
 * @brief File that tests the ToneMapping class
 *
 * This file contains all the tests made
 * for the ToneMapping class.
*/

#include "test.hpp"
#include "tone_mapping.hpp"

int main()
{    
    Tests t = Tests("TONE MAPPING TESTS");

    // Tests clamping
    t.addTest(Test::EXPECT_EQ(ToneMapping::clamping(2).evaluate(0.5),0.5F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::clamping(2).evaluate(1),1.0F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::clamping(2).evaluate(2),1.0F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::clamping(2).evaluate(1.5),1.0F));

    // Tests equalization
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization(1).evaluate(0.5),0.5F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization(2).evaluate(2),1.0F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization(10).evaluate(1),0.1F));

    // Tests equalization_clamping
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization_clamping(1,2).evaluate(0.5),0.5F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization_clamping(1,2).evaluate(1.1),1.0F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization_clamping(5,10).evaluate(0.5),0.1F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::equalization_clamping(7,10).evaluate(7),1.0F));


    // Tests gamma
    t.addTest(Test::EXPECT_EQ(ToneMapping::gamma(1,2).evaluate(2),1.0F));
    t.addTest(Test::EXPECT_EQ(ToneMapping::gamma(2,2).evaluate(1),0.25F));

    // Tests evaluate method
    t.addTest(Test::EXPECT_EXC([](){ToneMapping::clamping(1).evaluate(1.1);}));
    t.addTest(Test::EXPECT_EXC([](){ToneMapping::clamping(1).evaluate(-0.1);}));

    return t.runAll();
}