
#include "test.hpp"

#include "geometry/cylinder.hpp"


int main()
{
    Tests t = Tests("TESTS cylinder");

    Cylinder c = Cylinder(Geometric::point0(), 1.0F, Geometric::vector(0,0,1));

    Ray r1 = Ray(Geometric::point(-2,0,0), Geometric::vector(1,0,0));
    Ray r2 = Ray(Geometric::point(-1,0,1), Geometric::vector(0,0,1));
    Ray r3 = Ray(Geometric::point(-2,0,1), Geometric::vector(1,0,-1));
    Ray r4 = Ray(Geometric::point(-1,1,0), Geometric::vector(1,-1,0));

    Ray r5 = Ray(Geometric::point(0,0,3), Geometric::vector(0,0,-1));

    Ray r6 = Ray(Geometric::point(0,0,-3), Geometric::vector(0,0,1));

    Intersection i1;

    t.addTest("1", Test::EXPECT_EQ(c.intersect_with_ray(r1, i1), true));
    t.addTest("2", Test::EXPECT_EQ(i1.distance(), 1.0F));
    t.addTest("3", Test::EXPECT_EQ(i1.normal(), Geometric::vector(-1,0,0)));

    t.addTest("4", Test::EXPECT_EQ(c.intersect_with_ray(r2, i1), true));
    t.addTest("5", Test::EXPECT_EQ(i1.distance(), 0.0F));
    t.addTest("6", Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,1)));
    t.addTest("7", Test::EXPECT_EQ(i1.point(), Geometric::point(-1,0,1)));


    t.addTest("8",Test::EXPECT_EQ(c.intersect_with_ray(r3, i1), true));
    t.addTest("9",Test::EXPECT_EQ(i1.distance(), sqrt(2)));
    t.addTest("10",Test::EXPECT_EQ(i1.normal(), Geometric::vector(-1,0,0)));

    t.addTest("11",Test::EXPECT_EQ(c.intersect_with_ray(r4, i1), true));
    t.addTest("12",Test::EXPECT_EQ(i1.distance(), sqrt(2)-1));
    t.addTest("13",Test::EXPECT_EQ(i1.normal(), Geometric::vector(-1,1,0).normalize()));

    t.addTest("14",Test::EXPECT_EQ(c.intersect_with_ray(r5, i1), true));
    t.addTest("15",Test::EXPECT_EQ(i1.distance(), 2.0F));
    t.addTest("16",Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,1)));
    t.addTest("17",Test::EXPECT_EQ(i1.point(), Geometric::point(0,0,1)));

    t.addTest("18",Test::EXPECT_EQ(c.intersect_with_ray(r6, i1), true));
    t.addTest("19",Test::EXPECT_EQ(i1.distance(), 3.0F));
    t.addTest("20",Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,-1)));
    t.addTest("21",Test::EXPECT_EQ(i1.point(), Geometric::point(0,0,0)));

    return t.runAll();
}