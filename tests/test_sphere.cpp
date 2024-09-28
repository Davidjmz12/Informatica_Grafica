#include <math.h>

#include "test.hpp"
#include "sphere.hpp"

int main()
{
    Tests t = Tests("TESTS SPHERE");

    Sphere s = Sphere(Geometric::point0(), Geometric::vector(0,0,2), Geometric::point(1,0,0));
    Base b = Base(Geometric::point(1/sqrt(2),0,1/sqrt(2)), Geometric::vector(0,1,0), Geometric::vector(-1/sqrt(2),0,1/sqrt(2)), Geometric::vector(1/sqrt(2),0,1/sqrt(2)));
    Base b2 = Base(Geometric::point(0,1,0), Geometric::vector(-1,0,0), Geometric::vector(0,0,1), Geometric::vector(0,1,0));

    t.addTest("1",Test::EXPECT_EQ(s.base_point(M_PI_4,0), b));
    t.addTest("2",Test::EXPECT_EQ(s.base_point(M_PI_2,M_PI_2), b2));

    return t.runAll();
}