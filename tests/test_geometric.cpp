#include <math.h>

#include "test.hpp"
#include "geometric.hpp"

int main()
{
    Tests t = Tests("GEOMETRIC_TEST");

    Geometric p = Geometric::point(1,1,1);
    Geometric e1 = Geometric::vector(1,0,0);
    Geometric e2 = Geometric::vector(0,1,0);
    Geometric e3 = Geometric::vector(0,0,1);
    Geometric v1 = Geometric::vector(1,1,1);
    Geometric v2 = Geometric::vector(4,5,8.2);
    float norm = v2.norm();
    Geometric v2_n = Geometric::vector(4/norm,5/norm,8.2/norm);
    Geometric e1_4 = Geometric::vector(4,0,0);
    Geometric v1xv2 = Geometric::vector((float)3.2,(float)-4.2,(float)1);

    //Check the constructors and the is_point / is_vector methodes
    t.addTest(Test::EXPECT_EQ(p.is_point(), true));
    t.addTest(Test::EXPECT_EQ(p.is_vector(), false));
    t.addTest(Test::EXPECT_EQ(e1.is_point(), false));
    t.addTest(Test::EXPECT_EQ(e1.is_vector(), true));

    //Check the norm method
    t.addTest(Test::EXPECT_EQ(e1.norm(), (float)1.0));
    t.addTest(Test::EXPECT_EQ(v1.norm(), (float)sqrt(3)));
    t.addTest(Test::EXPECT_EXC([&p] {p.norm();}));

    //Check the normalize method
    t.addTest(Test::EXPECT_EQ(e1_4.normalize(), Geometric::vector(1,0,0)));
    t.addTest(Test::EXPECT_EQ(v2.normalize(), v2_n));
    t.addTest(Test::EXPECT_EXC([&p] {p.normalize();}));

    //Check the dot product
    t.addTest(Test::EXPECT_EQ(e1.dot(e2), (float)0));
    t.addTest(Test::EXPECT_EQ(v1.dot(v2), (float)17.2));
    t.addTest(Test::EXPECT_EXC([&p,&e1]{p.dot(e1);}));
    t.addTest(Test::EXPECT_EXC([&e1,&p]{e1.dot(p);}));
    t.addTest(Test::EXPECT_EXC([&p] {p.dot(p);}));

    //Check the cross product
    t.addTest(Test::EXPECT_EQ(e1.cross(e2), e3));
    t.addTest(Test::EXPECT_EQ(e2.cross(e3), e1));
    t.addTest(Test::EXPECT_EQ(e3.cross(e1), e2));
    t.addTest(Test::EXPECT_EQ(e2.cross(e1), e3 * -1));
    t.addTest(Test::EXPECT_EQ(e3.cross(e2), e1 * -1));
    t.addTest(Test::EXPECT_EQ(e1.cross(e3), e2 * -1));
    t.addTest(Test::EXPECT_EQ(v1.cross(v2), v1xv2));

    t.runAll();
}