
#include "test.hpp"

#include "geometry/triangle.hpp"

int main()
{

    Tests t = Tests("TEST TRIANGLE");

    Triangle tr= Triangle(Point(1,2,3),Point(0,5,0),Point(3,3,3));

    Ray r1 = Ray(Point(0,0,0),Vector(0,1,0));
    Ray r2 = Ray(Point(0,0,0),Vector(0.5,1,1));
    Ray r3 = Ray(Point(0,5,0),Vector(1,-3,3));
    Ray r4 = Ray(Point(1,5.5,0),Vector(1,-3,3));

    Ray r5 = Ray(Point(1.5,3,3),Vector(-0.5,-1,-1));

    Ray r6 = Ray(Point(0,0,0),Vector(0,0,1));
    Intersection i1;
    t.addTest("1", Test::EXPECT_EQ(tr.intersect_with_ray(r1,i1),false));

    t.addTest("2", Test::EXPECT_EQ(tr.intersect_with_ray(r2,i1),true));
    t.addTest("3", Test::EXPECT_EQ(i1.get_point(),Point(60.0/46,60.0/23,60.0/23)));
    t.addTest("4", Test::EXPECT_EQ(i1.get_normal(),Vector(3,-6,-7).normalize()));
    t.addTest("5", Test::EXPECT_EQ(i1.get_distance(),Vector(60.0/46,60.0/23,60.0/23).norm()));

    t.addTest("6", Test::EXPECT_EQ(tr.intersect_with_ray(r3,i1),false));
    t.addTest("7", Test::EXPECT_EQ(tr.intersect_with_ray(r4,i1),false));

    t.addTest("8", Test::EXPECT_EQ(tr.intersect_with_ray(r5,i1),true));
    t.addTest("9", Test::EXPECT_EQ(i1.get_point(),Point(60.0/46,60.0/23,60.0/23)));
    t.addTest("10", Test::EXPECT_EQ(i1.get_normal(),Vector(-3,6,7).normalize()));
    t.addTest("11", Test::EXPECT_EQ(i1.get_distance(),(Point(1.5,3,3)-Point(60.0/46,60.0/23,60.0/23)).norm()));

    t.addTest("12", Test::EXPECT_EQ(tr.intersect_with_ray(r6,i1),false));
    return t.runAll();
}