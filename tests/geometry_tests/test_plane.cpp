#include "geometry/plane.hpp"
#include "test.hpp"

int main()
{
    Tests t = Tests("TESTS plane");

    Plane p = Plane(Geometric::point0(), Geometric::vector(0,0,1));
    Plane p2 = Plane(Geometric::point(1,2,3), Geometric::vector(3,2,1));

    Ray r1 = Ray(Geometric::point(-2,0,0), Geometric::vector(1,0,0));
    Ray r2 = Ray(Geometric::point0(), Geometric::vector(0,0,1));
    Ray r3 = Ray(Geometric::point0(), Geometric::vector(-1,1,1));
    Ray r4 = Ray(Geometric::point0(), Geometric::vector(1,-4,5));
    Ray r5 = Ray(Geometric::point(4,0,0), Geometric::vector(-1,0,0));
    Intersection i1;

    // All ray intersects with the plane
    t.addTest("1", Test::EXPECT_EQ(p.intersect_with_ray(r1, i1), false));

    t.addTest("2", Test::EXPECT_EQ(p.intersect_with_ray(r2, i1), true));
    t.addTest("3", Test::EXPECT_EQ(i1.distance(), 0.0F));
    
    t.addTest("4",Test::EXPECT_EQ(p2.intersect_with_ray(r2, i1), true));
    t.addTest("5",Test::EXPECT_EQ(i1.distance(), 10.0F));
    t.addTest("6",Test::EXPECT_EQ(i1.normal(), (Geometric::vector(3,2,1)*(-1)).normalize()));
    t.addTest("7",Test::EXPECT_EQ(i1.point(), Geometric::point(0,0,10)));

    // All ray does not intersect with the plane
    t.addTest("8",Test::EXPECT_EQ(p2.intersect_with_ray(r3, i1), false));
    t.addTest("9",Test::EXPECT_EQ(p2.intersect_with_ray(r4, i1), false));

    t.addTest("10",Test::EXPECT_EQ(p2.intersect_with_ray(r5, i1), true));
    t.addTest("11",Test::EXPECT_EQ(i1.distance(), 2/3.0F));
    t.addTest("12",Test::EXPECT_EQ(i1.normal(), Geometric::vector(3,2,1).normalize()));
    t.addTest("13",Test::EXPECT_EQ(i1.point(), Geometric::point(10/3.0F,0,0)));

    return t.runAll();

}