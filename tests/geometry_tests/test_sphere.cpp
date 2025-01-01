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

    std::shared_ptr<BRDF> brdf = std::make_shared<BRDF>();
    Tests t = Tests("SPHERE TEST");

    Sphere s = Sphere(Point(), 1, brdf);
    Ray r = Ray(Point(-2,0,0),Vector(1,0,0));
    IntersectionObject res = IntersectionObject();
    t.addTest("1", Test::EXPECT_EQ(s.intersect_with_ray(r,res),true));
    t.addTest("2", Test::EXPECT_EQ(res.get_distance(),1));
    t.addTest("3", Test::EXPECT_EQ(res.get_int_point(),Point(-1,0,0)));
    t.addTest("4", Test::EXPECT_EQ(res.get_normal(),Vector(-1,0,0)));
    t.addTest("5", Test::EXPECT_EQ(res.is_entering(), true));


    Sphere s2 = Sphere(Point(2,3,5), 2, brdf);
    Ray r2 = Ray(Point(6,0,0),Vector(-2,3,5));
    t.addTest("6", Test::EXPECT_EQ(s2.intersect_with_ray(r2,res),true));
    t.addTest("7", Test::EXPECT_EQ(res.get_distance(),sqrt(38)));
    t.addTest("8", Test::EXPECT_EQ(res.get_int_point(),Point(4,3,5)));  
    t.addTest("9", Test::EXPECT_EQ(res.get_normal(),Vector(1,0,0)));
    t.addTest("10", Test::EXPECT_EQ(res.is_entering(), true));


    Ray r3 = Ray(Point(6,0,0),Vector(0,0,1));
    t.addTest("11", Test::EXPECT_EQ(s2.intersect_with_ray(r3,res),false));


    Ray r4 = Ray(Point(6,0,0),Vector(-4,3,3));
    t.addTest("12", Test::EXPECT_EQ(s2.intersect_with_ray(r4,res),true));
    t.addTest("13", Test::EXPECT_EQ(res.get_distance(),sqrt(34)));
    t.addTest("14", Test::EXPECT_EQ(res.get_int_point(),Point(2,3,3)));
    t.addTest("15", Test::EXPECT_EQ(res.get_normal(),Vector(0,0,-1)));
    t.addTest("16", Test::EXPECT_EQ(res.is_entering(), true));


    Sphere s3 = Sphere(Point(0,0,0), 1, brdf);
    Ray r5 = Ray(Point(0,0,-1),Vector(0,0,1));
    t.addTest("17", Test::EXPECT_EQ(s3.intersect_with_ray(r5,res),true));
    t.addTest("18", Test::EXPECT_EQ(res.get_distance(),2));
    t.addTest("19", Test::EXPECT_EQ(res.get_int_point(),Point(0,0,1)));
    t.addTest("20", Test::EXPECT_EQ(res.get_normal(),Vector(0,0,-1)));
    t.addTest("21", Test::EXPECT_EQ(res.is_entering(), false));

    return t.runAll();
}   