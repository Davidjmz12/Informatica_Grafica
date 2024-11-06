#include "test/test.hpp"

#include "geometry/disk.hpp"

int main()
{

    Tests t = Tests("TESTS disk");
    Property property = Property();
    Disk d1 = Disk(Point(1,1,0), Vector(0,0,1), 1,property);

    Ray r1 = Ray(Point(), Vector(1,0,0));
    Ray r2 = Ray(Point(0,1,0), Vector(1,0,0));
    Ray r3 = Ray(Point(1,1,1), Vector(0,0,-1));
    Ray r4 = Ray(Point(1,1,-1), Vector(0,0,1));
    Ray r5 = Ray(Point(0,1,-1), Vector(0,0,1));

    IntersectionObject i1;

    t.addTest("1", Test::EXPECT_EQ(d1.intersect_with_ray(r1, i1), false));
    t.addTest("2", Test::EXPECT_EQ(d1.intersect_with_ray(r2, i1), false));
    t.addTest("3", Test::EXPECT_EQ(d1.intersect_with_ray(r3, i1), true));
    
    t.addTest("4", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("5", Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,1)));
    t.addTest("6", Test::EXPECT_EQ(i1.get_origin(), Point(1,1,0)));

    t.addTest("7", Test::EXPECT_EQ(d1.intersect_with_ray(r4, i1), true));
    t.addTest("8", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("9", Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,-1)));
    t.addTest("10", Test::EXPECT_EQ(i1.get_origin(), Point(1,1,0)));

    t.addTest("11", Test::EXPECT_EQ(d1.intersect_with_ray(r5, i1), true));
    t.addTest("12", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("13", Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,-1)));
    t.addTest("14", Test::EXPECT_EQ(i1.get_origin(), Point(0,1,0)));

    return t.runAll();
}