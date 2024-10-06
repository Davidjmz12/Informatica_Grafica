/**
 * @file test_sphere.cpp
 * @brief File that tests the Sphere class.
 * @author David Tizne Ondiviela.
 *
 * This file contains all the tests that has been made
 * for the Sphere class.
*/

#include "test.hpp"
#include "geometry/sphere.hpp"

int main()
{
    Tests t = Tests("SPHERE TEST");

    Sphere s = Sphere(Point(), 1);
    Ray r = Ray(Point(-2,0,0),Vector(1,0,0));
    Intersection res = Intersection();

    t.addTest("1", Test::EXPECT_EQ(s.intersect_with_ray(r,res),true));
    t.addTest("2", Test::EXPECT_EQ(res,Intersection(1,Vector(-1,0,0),Point(-1,0,0))));

    Sphere s2 = Sphere(Point(2,3,5), 2);
    Ray r2 = Ray(Point(6,0,0),Vector(-2,3,5));

    t.addTest("3", Test::EXPECT_EQ(s2.intersect_with_ray(r2,res),true));
    t.addTest("4", Test::EXPECT_EQ(res,Intersection(sqrt(38),Vector(1,0,0),Point(4,3,5))));

    Ray r3 = Ray(Point(6,0,0),Vector(0,0,1));
    t.addTest("5", Test::EXPECT_EQ(s2.intersect_with_ray(r3,res),false));

    Ray r4 = Ray(Point(6,0,0),Vector(-4,3,3));
    t.addTest("6", Test::EXPECT_EQ(s2.intersect_with_ray(r4,res),true));
    t.addTest("7", Test::EXPECT_EQ(res,Intersection(sqrt(34),Vector(0,0,-1),Point(2,3,3))));

    return t.runAll();
}