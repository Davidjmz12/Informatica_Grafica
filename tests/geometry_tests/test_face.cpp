#include "geometry/face.hpp"
#include "test/test.hpp"

int main()
{
    Tests t = Tests("TESTS FACE");

    Face f1 = Face(Vector(1,1,1),Vector(0,-1,1),Vector(-1,0,1),Point(1,2,3),Property());

    Ray r1 = Ray(Point(0,0,0),Vector(1,2,3));
    Ray r2 = Ray(Point(2,4,6),Vector(-1,-2,-3));
    Ray r3 = Ray(Point(2,2,2),Vector(-1,-1,2));
    Ray r4 = Ray(Point(1.5,1.5,3),Vector(-1,1,0));

    IntersectionObject i1 = IntersectionObject();

    t.addTest("1",Test::EXPECT_EQ(f1.intersect_with_ray(r1,i1),true));
    t.addTest("2",Test::EXPECT_EQ(i1.get_int_point(),Point(1,2,3)));
    t.addTest("3",Test::EXPECT_EQ(i1.get_normal(),Vector(-1,-1,-1).normalize()));
    t.addTest("4",Test::EXPECT_EQ(i1.get_distance(),Vector(1,2,3).norm()));
    
    t.addTest("5",Test::EXPECT_EQ(f1.intersect_with_ray(r2,i1),true));
    t.addTest("6",Test::EXPECT_EQ(i1.get_int_point(),Point(1,2,3)));
    t.addTest("7",Test::EXPECT_EQ(i1.get_normal(),Vector(1,1,1).normalize()));
    t.addTest("8",Test::EXPECT_EQ(i1.get_distance(),Vector(1,2,3).norm()));
    
    t.addTest("9",Test::EXPECT_EQ(f1.intersect_with_ray(r3,i1),false));
    t.addTest("10",Test::EXPECT_EQ(f1.intersect_with_ray(r4,i1),false));

    return t.runAll();

}