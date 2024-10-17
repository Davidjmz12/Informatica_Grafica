
#include "test.hpp"

#include "geometry/cylinder.hpp"


int main()
{
    Tests t = Tests("TESTS cylinder");
    Property property = Property();

    Cylinder c = Cylinder(Point(), 1.0F, Vector(0,0,1), property);

    Ray r1 = Ray(Point(-2,0,0), Vector(1,0,0));
    Ray r2 = Ray(Point(-1,0,2), Vector(0,0,-1));
    Ray r3 = Ray(Point(-2,0,1), Vector(1,0,-1));
    Ray r4 = Ray(Point(-1,1,0), Vector(1,-1,0));

    Ray r5 = Ray(Point(0,0,3), Vector(0,0,-1));

    Ray r6 = Ray(Point(0,0,-3), Vector(0,0,1));

    Intersection i1;

    t.addTest("1", Test::EXPECT_EQ(c.intersect_with_ray(r1, i1), true));
    t.addTest("2", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("3", Test::EXPECT_EQ(i1.get_normal(), Vector(-1,0,0)));

    t.addTest("4", Test::EXPECT_EQ(c.intersect_with_ray(r2, i1), true));
    t.addTest("5", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("6", Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,1)));
    t.addTest("7", Test::EXPECT_EQ(i1.get_point(), Point(-1,0,1)));


    t.addTest("8",Test::EXPECT_EQ(c.intersect_with_ray(r3, i1), true));
    t.addTest("9",Test::EXPECT_EQ(i1.get_distance(), sqrt(2)));
    t.addTest("10",Test::EXPECT_EQ(i1.get_normal(), Vector(-1,0,0)));

    t.addTest("11",Test::EXPECT_EQ(c.intersect_with_ray(r4, i1), true));
    t.addTest("12",Test::EXPECT_EQ(i1.get_distance(), sqrt(2)-1));
    t.addTest("13",Test::EXPECT_EQ(i1.get_normal(), Vector(-1,1,0).normalize()));

    t.addTest("14",Test::EXPECT_EQ(c.intersect_with_ray(r5, i1), true));
    t.addTest("15",Test::EXPECT_EQ(i1.get_distance(), 2.0F));
    t.addTest("16",Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,1)));
    t.addTest("17",Test::EXPECT_EQ(i1.get_point(), Point(0,0,1)));

    t.addTest("18",Test::EXPECT_EQ(c.intersect_with_ray(r6, i1), true));
    t.addTest("19",Test::EXPECT_EQ(i1.get_distance(), 3.0F));
    t.addTest("20",Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,-1)));
    t.addTest("21",Test::EXPECT_EQ(i1.get_point(), Point()));

    return t.runAll();
}