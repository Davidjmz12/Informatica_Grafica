
#include "test/test.hpp"

#include "geometry/cylinder.hpp"


int main()
{
    Tests t = Tests("TESTS cylinder");
    std::shared_ptr<BRDF> brdf = std::make_shared<BRDF>();

    Cylinder c = Cylinder(Point(), 1.0F, Vector(0,0,1), brdf);

    Ray r1 = Ray(Point(-2,0,0), Vector(1,0,0));
    Ray r2 = Ray(Point(-1,0,2), Vector(0,0,-1));
    Ray r3 = Ray(Point(-2,0,1), Vector(1,0,-1));
    Ray r4 = Ray(Point(-1,1,0), Vector(1,-1,0));

    Ray r5 = Ray(Point(0,0,3), Vector(0,0,-1));

    Ray r6 = Ray(Point(0,0,-3), Vector(0,0,1));

    Cylinder c2 = Cylinder(Point(2, 2, 0), 2.0F, Vector(0,0,2), brdf);

    Ray r7 = Ray(Point(2,2,3), Vector(0,0,1));
    Ray r8 = Ray(Point(2,2,3), Vector(0,0,-1));
    Ray r9 = Ray(Point(-2,2,1), Vector(1,0,0));
    Ray r10 = Ray(Point(2,2,-3), Vector(0,0,1));
    Ray r11 = Ray(Point(2,2,-3), Vector(0,0,-1));
    Ray r12 = Ray(Point(2,2,0), Vector(0,0,1));
    Ray r13 = Ray(Point(2,2,0), Vector(0,0,-1));
    Ray r14 = Ray(Point(2,2,2), Vector(0,-2,-1));
    Ray r15 = Ray(Point(2,4,3), Vector(0,-2,-1));


    IntersectionObject i1;

    t.addTest("1", Test::EXPECT_EQ(c.intersect_with_ray(r1, i1), true));
    t.addTest("2", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("3", Test::EXPECT_EQ(i1.get_normal(), Vector(-1,0,0)));

    t.addTest("4", Test::EXPECT_EQ(c.intersect_with_ray(r2, i1), true));
    t.addTest("5", Test::EXPECT_EQ(i1.get_distance(), 1.0F));
    t.addTest("6", Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,1)));
    t.addTest("7", Test::EXPECT_EQ(i1.get_int_point(), Point(-1,0,1)));


    t.addTest("8",Test::EXPECT_EQ(c.intersect_with_ray(r3, i1), true));
    t.addTest("9",Test::EXPECT_EQ(i1.get_distance(), sqrt(2)));
    t.addTest("10",Test::EXPECT_EQ(i1.get_normal(), Vector(-1,0,0)));

    t.addTest("11",Test::EXPECT_EQ(c.intersect_with_ray(r4, i1), true));
    t.addTest("12",Test::EXPECT_EQ(i1.get_distance(), sqrt(2)-1));
    t.addTest("13",Test::EXPECT_EQ(i1.get_normal(), Vector(-1,1,0).normalize()));

    t.addTest("14",Test::EXPECT_EQ(c.intersect_with_ray(r5, i1), true));
    t.addTest("15",Test::EXPECT_EQ(i1.get_distance(), 2.0F));
    t.addTest("16",Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,1)));
    t.addTest("17",Test::EXPECT_EQ(i1.get_int_point(), Point(0,0,1)));

    t.addTest("18",Test::EXPECT_EQ(c.intersect_with_ray(r6, i1), true));
    t.addTest("19",Test::EXPECT_EQ(i1.get_distance(), 3.0F));
    t.addTest("20",Test::EXPECT_EQ(i1.get_normal(), Vector(0,0,-1)));
    t.addTest("21",Test::EXPECT_EQ(i1.get_int_point(), Point()));


    IntersectionObject i2;
    t.addTest("22",Test::EXPECT_EQ(c2.intersect_with_ray(r7, i2), false));

    t.addTest("23",Test::EXPECT_EQ(c2.intersect_with_ray(r8, i2), true));
    t.addTest("24",Test::EXPECT_EQ(i2.get_distance(), 1.0F));
    t.addTest("25",Test::EXPECT_EQ(i2.get_normal(), Vector(0,0,1)));

    t.addTest("26",Test::EXPECT_EQ(c2.intersect_with_ray(r9, i2), true));
    t.addTest("27",Test::EXPECT_EQ(i2.get_distance(), 2.0F));
    t.addTest("28",Test::EXPECT_EQ(i2.get_normal(), Vector(-1,0,0)));


    t.addTest("29",Test::EXPECT_EQ(c2.intersect_with_ray(r10, i2), true));
    t.addTest("30",Test::EXPECT_EQ(i2.get_distance(), 3.0F));
    t.addTest("31",Test::EXPECT_EQ(i2.get_normal(), Vector(0,0,-1)));

    t.addTest("32",Test::EXPECT_EQ(c2.intersect_with_ray(r11, i2), false));

    t.addTest("33",Test::EXPECT_EQ(c2.intersect_with_ray(r12, i2), true));
    t.addTest("34",Test::EXPECT_EQ(i2.get_distance(), 2.0F));
    t.addTest("35",Test::EXPECT_EQ(i2.get_normal(), Vector(0,0,-1)));

    t.addTest("36",Test::EXPECT_EQ(c2.intersect_with_ray(r13, i2), false));

    t.addTest("37",Test::EXPECT_EQ(c2.intersect_with_ray(r14, i2), true));
    t.addTest("38",Test::EXPECT_EQ(i2.get_distance(), Vector(0,-2,-1).norm()));
    t.addTest("39",Test::EXPECT_EQ(i2.get_normal(), Vector(0,-1,0)));

    t.addTest("40",Test::EXPECT_EQ(c2.intersect_with_ray(r15, i2), true));
    t.addTest("41",Test::EXPECT_EQ(i2.get_distance(), Vector(0,-2,-1).norm()));
    t.addTest("42",Test::EXPECT_EQ(i2.get_normal(), Vector(0,0,1)));

    return t.runAll();
}