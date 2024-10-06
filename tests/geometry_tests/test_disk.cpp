#include "test.hpp"

#include "geometry/disk.hpp"

int main()
{

    Tests t = Tests("TESTS disk");

    Disk d1 = Disk(Geometric::point(1,1,0), Geometric::vector(0,0,1), 1);

    Ray r1 = Ray(Geometric::point0(), Geometric::vector(1,0,0));
    Ray r2 = Ray(Geometric::point(0,1,0), Geometric::vector(1,0,0));
    Ray r3 = Ray(Geometric::point(1,1,1), Geometric::vector(0,0,-1));
    Ray r4 = Ray(Geometric::point(1,1,-1), Geometric::vector(0,0,1));
    Ray r5 = Ray(Geometric::point(0,1,-1), Geometric::vector(0,0,1));

    Intersection i1;

    t.addTest("1", Test::EXPECT_EQ(d1.intersect_with_ray(r1, i1), false));
    t.addTest("2", Test::EXPECT_EQ(d1.intersect_with_ray(r2, i1), false));
    t.addTest("3", Test::EXPECT_EQ(d1.intersect_with_ray(r3, i1), true));
    
    t.addTest("4", Test::EXPECT_EQ(i1.distance(), 1.0F));
    t.addTest("5", Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,1)));
    t.addTest("6", Test::EXPECT_EQ(i1.point(), Geometric::point(1,1,0)));

    t.addTest("7", Test::EXPECT_EQ(d1.intersect_with_ray(r4, i1), true));
    t.addTest("8", Test::EXPECT_EQ(i1.distance(), 1.0F));
    t.addTest("9", Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,-1)));
    t.addTest("10", Test::EXPECT_EQ(i1.point(), Geometric::point(1,1,0)));

    t.addTest("11", Test::EXPECT_EQ(d1.intersect_with_ray(r5, i1), true));
    t.addTest("12", Test::EXPECT_EQ(i1.distance(), 1.0F));
    t.addTest("13", Test::EXPECT_EQ(i1.normal(), Geometric::vector(0,0,-1)));
    t.addTest("14", Test::EXPECT_EQ(i1.point(), Geometric::point(0,1,0)));

    return t.runAll();
}