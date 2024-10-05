/**
 * @file test_geometric.cpp
 * @brief File that tests the Geometric class
 *
 * This file contains all the tests that has been made
 * for the Geometric class.
*/
#include <math.h>

#include "test.hpp"
#include "spatial_element/vector.hpp"

int main()
{
    Tests t = Tests("SPATIAL ELEMENTS TEST");

    // Check definitios, is_point, is_vector
    Vector v = Vector();
    Point p = Point();

    t.addTest("1", Test::EXPECT_EQ(v,Vector(0,0,0)));
    t.addTest("2", Test::EXPECT_EQ(v.is_vector(),true));
    t.addTest("3", Test::EXPECT_EQ(v.is_point(),false));
    t.addTest("4", Test::EXPECT_EQ(p,Point(0,0,0)));
    t.addTest("5", Test::EXPECT_EQ(p.is_vector(),false));
    t.addTest("6", Test::EXPECT_EQ(p.is_point(),true));

    // Check norm
    Vector e1 = Vector(1,0,0);
    Vector v2 = Vector(3,4,5);

    t.addTest("7", Test::EXPECT_EQ(e1.norm(),1));
    t.addTest("8", Test::EXPECT_EQ(v2.norm(),sqrt(50)));

    // Check operators and normalizate
    t.addTest("9", Test::EXPECT_EQ(e1*4, Vector(4,0,0)));
    t.addTest("10", Test::EXPECT_EQ(e1+v2, Vector(4,4,5)));
    t.addTest("11", Test::EXPECT_EQ(e1-v2, Vector(-2,-4,-5)));
    t.addTest("12", Test::EXPECT_EQ(v2/sqrt(50), v2.normalize()));

    Point p2 = Point(4,5,6);
    t.addTest("13", Test::EXPECT_EQ(p2+v2,Point(7,9,11)));
    t.addTest("14", Test::EXPECT_EQ(v2+p2,Point(7,9,11)));
    t.addTest("15", Test::EXPECT_EQ(p2-p,Vector(p2)));
    t.addTest("16", Test::EXPECT_EQ(p2-e1, Point(3,5,6)));

    // Dot and cross
    Vector v3 = Vector(-1,2,3);
    Vector v4 = Vector(8,3,4.5);
    t.addTest("17", Test::EXPECT_EQ(v3.dot(&v4), 11.5));
    t.addTest("18", Test::EXPECT_EQ(v3.cross(&v4), Vector(0,28.5,-19)));

    // Linearly dependent
    t.addTest("19", Test::EXPECT_EQ(e1.linearly_dependent(&v2),false));
    t.addTest("20", Test::EXPECT_EQ((v3*3.8).linearly_dependent(&v3),true));

    // Base
    Vector e2 = Vector(0,1,0);
    Vector e3 = Vector(0,0,1);
    t.addTest("21", Test::EXPECT_EQ(e1.is_base(&e2,&e3),true));
    t.addTest("22", Test::EXPECT_EQ((e2*-9.7).is_base(&e2,&e3),false));

    return t.runAll();
}