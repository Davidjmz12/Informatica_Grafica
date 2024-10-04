/**
 * @file test_ellipsoid.cpp
 * @brief File that tests the Ellipsoid class.
 *
 * This file contains all the tests that has been made
 * for the Ellipsoid class.
*/

#include "test.hpp"
#include "ellipsoid.hpp"

int main()
{
    Tests t = Tests("ELLIPSOID_TEST");

    Ellipsoid e = Ellipsoid(1,2,3,Geometric::point0());
    Ray r = Ray(Geometric::point(-2,0,0),Geometric::vector(1,0,0));
    Intersection res = Intersection();

    t.addTest("1", Test::EXPECT_EQ(e.intersect_with_ray(r,res),true));
    t.addTest("2", Test::EXPECT_EQ(res,Intersection(1,Geometric::vector(-1,0,0),Geometric::point(-1,0,0))));

    return t.runAll();
}