#include "test/test.hpp"

#include "geometry/cone.hpp"

int main()
{

    Tests t = Tests("TEST CONE");

    Cone c = Cone(Point(0,0,0), Vector(0,0,1), 1, Property());
    Cone c2 = Cone(Point(1,1,1),Vector(1,1,1), 0.5, Property());
    Ray r1 = Ray(Point(0,0,-1), Vector(0,0,1));
    Ray r2 = Ray(Point(0,0,-0), Vector(1,1,1));
    Ray r3 = Ray(Point(3,3,3), Vector(-1,-1,-1));
    Ray r4 = Ray(Point(2,0,2), Point(1.85,2,1.8)-Point(2,0,2));

    Intersection i;

    t.addTest("1",Test::EXPECT_EQ(c.intersect_with_ray(r1, i), true));
    t.addTest("2",Test::EXPECT_EQ(i.get_distance(), 1));
    t.addTest("3",Test::EXPECT_EQ(i.get_normal(), Vector(0,0,-1)));
    t.addTest("4",Test::EXPECT_EQ(i.get_point(), Point(0,0,0)));

    t.addTest("5",Test::EXPECT_EQ(c2.intersect_with_ray(r2, i), true));
    t.addTest("6",Test::EXPECT_EQ(i.get_distance(), sqrt(3)));
    t.addTest("7",Test::EXPECT_EQ(i.get_normal(), Vector(-1,-1,-1).normalize()));
    t.addTest("8",Test::EXPECT_EQ(i.get_point(), Point(1,1,1)));

    //t.addTest("9",Test::EXPECT_EQ(c2.intersect_with_ray(r3, i), true));
    //t.addTest("10",Test::EXPECT_EQ(i.get_distance(), sqrt(12)));

    t.addTest("11",Test::EXPECT_EQ(c2.intersect_with_ray(r4, i), true));
    t.addTest("12",Test::EXPECT_EQ(i.get_distance(), sqrt(3)));
    t.addTest("13",Test::EXPECT_EQ(i.get_normal(), Vector(1,-1,1).normalize()));
    t.addTest("14",Test::EXPECT_EQ(i.get_point(), Point(1,0,1)));


    return t.runAll();
}