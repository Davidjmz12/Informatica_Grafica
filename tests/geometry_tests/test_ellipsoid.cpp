/**
 * @file test_ellipsoid.cpp
 * @brief File that tests the Ellipsoid class.
 * @author David Tizne Ondiviela.
 *
 * This file contains all the tests that has been made
 * for the Ellipsoid class.
*/

#include "test/test.hpp"
#include "geometry/ellipsoid.hpp"

int main()
{
    Tests t = Tests("ELLIPSOID_TEST");
    std::shared_ptr<BRDF> brdf = std::make_shared<BRDF>();
    Ellipsoid e = Ellipsoid(1,2,3,Point(), brdf);
    Ray r = Ray(Point(-2,0,0),Vector(1,0,0));
    IntersectionObject res = IntersectionObject();

    t.addTest("1", Test::EXPECT_EQ(e.intersect_with_ray(r,res),true));
    t.addTest("2", Test::EXPECT_EQ(res,IntersectionObject(1,Vector(-1,0,0),Point(-1,0,0), *brdf, r)));

    Ellipsoid e2 = Ellipsoid(3,2,1,Point(2,3,5), brdf);
    Ray r2 = Ray(Point(6,0,0),Vector(-4,3,4));

    t.addTest("3", Test::EXPECT_EQ(e2.intersect_with_ray(r2,res),true));
    t.addTest("4", Test::EXPECT_EQ(res,IntersectionObject(sqrt(41),Vector(0,0,-1),Point(2,3,4), *brdf, r)));

    Ray r3 = Ray(Point(6,0,0),Vector(0,0,1));
    t.addTest("5", Test::EXPECT_EQ(e2.intersect_with_ray(r3,res),false));

    Ray r4 = Ray(Point(6,0,0),Vector(-1,3,5));
    t.addTest("6", Test::EXPECT_EQ(e2.intersect_with_ray(r4,res),true));
    t.addTest("7", Test::EXPECT_EQ(res,IntersectionObject(sqrt(35),Vector(1,0,0),Point(5,3,5), *brdf, r)));



    return t.runAll();
}