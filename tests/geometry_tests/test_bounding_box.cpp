#include "test/test.hpp"
#include "geometry/bounding_box.hpp"

int main()
{

    Tests t = Tests("TEST BOUNDING BOX");

    std::array<double, 6> bounds = {0, 1, 0, 1, 0, 1};
    std::array<double, 6> bounds2 = {-3, -2, 0, 1, 3, 6};

    BoundingBox bb = BoundingBox(bounds);
    BoundingBox bb2 = BoundingBox(bounds2);

    Ray r11 = Ray(Point(0, 0, 3), Vector(0, 0, -1));
    Ray r12 = Ray(Point(0, -1, 0), Vector(0, 1, 0));
    Ray r13 = Ray(Point(0, 0, 0), Vector(-1, -1, -1));
    Ray r14 = Ray(Point(0.5, 0.5, 0.5), Vector(1, 1, 1));
    Ray r15 = Ray(Point(1.5, 1.5, 1.5), Vector(1, 1, 1));
    Ray r16 = Ray(Point(2, 2, 2), Vector(1, 0, 0));
    Ray r17 = Ray(Point(2, 2, 2), Vector(0, 1, 0));
    Ray r18 = Ray(Point(2, 2, 2), Vector(0, 0, 1));
    Ray r19 = Ray(Point(-1, -1, -1), Vector(-1, -1, -1));

    Ray r20 = Ray(Point(0.5, 0.5, 0.5), Vector(1, 1, 1));


    t.addTest("1", Test::EXPECT_EQ(bb.intersect_with_ray(r11), true));
    t.addTest("2", Test::EXPECT_EQ(bb.intersect_with_ray(r12), true));
    t.addTest("3", Test::EXPECT_EQ(bb.intersect_with_ray(r13), true));
    t.addTest("4", Test::EXPECT_EQ(bb.intersect_with_ray(r14), true));
    t.addTest("5", Test::EXPECT_EQ(bb.intersect_with_ray(r15), false));
    t.addTest("6", Test::EXPECT_EQ(bb.intersect_with_ray(r16), false));
    t.addTest("7", Test::EXPECT_EQ(bb.intersect_with_ray(r17), false));
    t.addTest("8", Test::EXPECT_EQ(bb.intersect_with_ray(r18), false));
    t.addTest("9", Test::EXPECT_EQ(bb.intersect_with_ray(r19), false));

    t.addTest("10", Test::EXPECT_EQ(bb.intersect_with_ray(r20), true));

    return t.runAll();
}