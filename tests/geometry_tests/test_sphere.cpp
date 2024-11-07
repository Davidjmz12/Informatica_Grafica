/**
 * @file test_sphere.cpp
 * @brief File that tests the Sphere class.
 * @author David Tizne Ondiviela.
 *
 * This file contains all the tests that has been made
 * for the Sphere class.
*/

#include "test/test.hpp"
#include "geometry/sphere.hpp"

int main()
{

    Property property = Property();
    Tests t = Tests("SPHERE TEST");

    Sphere s = Sphere(Point(), 1,property);
    Ray r = Ray(Point(-2,0,0),Vector(1,0,0));
    IntersectionObject res = IntersectionObject();

    t.addTest("1", Test::EXPECT_EQ(s.intersect_with_ray(r,res),true));
    t.addTest("2", Test::EXPECT_EQ(res,IntersectionObject(1,Vector(-1,0,0),Point(-1,0,0),property, r)));

    Sphere s2 = Sphere(Point(2,3,5), 2,property);
    Ray r2 = Ray(Point(6,0,0),Vector(-2,3,5));

    t.addTest("3", Test::EXPECT_EQ(s2.intersect_with_ray(r2,res),true));
    t.addTest("4", Test::EXPECT_EQ(res,IntersectionObject(sqrt(38),Vector(1,0,0),Point(4,3,5),property, r)));

    Ray r3 = Ray(Point(6,0,0),Vector(0,0,1));
    t.addTest("5", Test::EXPECT_EQ(s2.intersect_with_ray(r3,res),false));

    Ray r4 = Ray(Point(6,0,0),Vector(-4,3,3));
    t.addTest("6", Test::EXPECT_EQ(s2.intersect_with_ray(r4,res),true));
    t.addTest("7", Test::EXPECT_EQ(res,IntersectionObject(sqrt(34),Vector(0,0,-1),Point(2,3,3),property, r)));

    Sphere s3 = Sphere(Point(0,0,0), 1, property);
    Ray r5 = Ray(Point(0,0,-1),Vector(0,0,1));
    t.addTest("8", Test::EXPECT_EQ(s3.intersect_with_ray(r5,res),true));
    t.addTest("9", Test::EXPECT_EQ(res,IntersectionObject(2,Vector(0,0,1),Point(0,0,1), property, r5)));

    return t.runAll();
}