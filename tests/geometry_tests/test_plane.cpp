#include "geometry/plane.hpp"
#include "test/test.hpp"

int main()
{
    Tests t = Tests("TESTS plane");
    Property property = Property();
    Plane p = Plane(Point(), Vector(0,0,1),property);
    Plane p2 = Plane(Point(1,2,3), Vector(3,2,1),property);

    Ray r1 = Ray(Point(-2,0,0), Vector(1,0,0));
    Ray r2 = Ray(Point(), Vector(0,0,1));
    Ray r3 = Ray(Point(), Vector(-1,1,1));
    Ray r4 = Ray(Point(), Vector(1,-4,5));
    Ray r5 = Ray(Point(4,0,0), Vector(-1,0,0));
    IntersectionObject i1;

    // All ray intersects with the plane
    t.addTest("1", Test::EXPECT_EQ(p.intersect_with_ray(r1, i1), false));

    t.addTest("2", Test::EXPECT_EQ(p.intersect_with_ray(r2, i1), true));
    t.addTest("3", Test::EXPECT_EQ(i1.get_distance(), 0.0F));
    
    t.addTest("4",Test::EXPECT_EQ(p2.intersect_with_ray(r2, i1), true));
    t.addTest("5",Test::EXPECT_EQ(i1.get_distance(), 10.0F));
    t.addTest("6",Test::EXPECT_EQ(i1.get_normal(), (Vector(3,2,1)*(-1)).normalize()));
    t.addTest("7",Test::EXPECT_EQ(i1.get_origin(), Point(0,0,10)));

    // All ray does not intersect with the plane
    t.addTest("8",Test::EXPECT_EQ(p2.intersect_with_ray(r3, i1), false));
    t.addTest("9",Test::EXPECT_EQ(p2.intersect_with_ray(r4, i1), false));

    t.addTest("10",Test::EXPECT_EQ(p2.intersect_with_ray(r5, i1), true));
    t.addTest("11",Test::EXPECT_EQ(i1.get_distance(), 2/3.0F));
    t.addTest("12",Test::EXPECT_EQ(i1.get_normal(), Vector(3,2,1).normalize()));
    t.addTest("13",Test::EXPECT_EQ(i1.get_origin(), Point(10/3.0F,0,0)));

    return t.runAll();

}