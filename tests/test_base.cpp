/**
 * @file test_base.cpp
 * @brief File that tests the Base class.
 *
 * This file contains all the tests that has been made
 * for the Base class.
*/

#include "test.hpp"
#include "base.hpp"

int main()
{
    Tests t = Tests("BASE TESTS");

    Base canonical = Base::canonic_base();
    Base v = Base(Geometric::point(1,1,1),Geometric::vector(1,1,0),
                  Geometric::vector(2,1,1),Geometric::vector(3,0,1));

    // TEST POINT
    t.addTest(Test::EXPECT_EQ(canonical.coord_into_canonical(Geometric::vector(0,0,0)),Geometric::vector0()));
    t.addTest(Test::EXPECT_EQ(canonical.coord_from_canonical(Geometric::vector(0,0,0)),Geometric::vector0()));
    //t.addTest(Test::EXPECT_EQ(canonical.point(2,3,-8.6), Geometric::point(2,3,-8.6)));
    //t.addTest(Test::EXPECT_EQ(v.point(1,-1,0),Geometric::point(0,1,0)));


    // TEST MATRIX
    t.addTest(Test::EXPECT_EQ(canonical.canonical_to_base(),Linear_Map::identity()));

    return t.runAll();
}