#include <math.h>

#include "test.hpp"
#include "planet.hpp"

int main()
{
    Tests t = Tests("TESTS planet");

    Planet s = Planet(Geometric::point0(), Geometric::vector(0,0,1), Geometric::point(1,0,0));
    Base b = Base(Geometric::point(1/sqrt(2),0,1/sqrt(2)), Geometric::vector(0,1,0), Geometric::vector(-1/sqrt(2),0,1/sqrt(2)), Geometric::vector(1/sqrt(2),0,1/sqrt(2)));
    Base b2 = Base(Geometric::point(0,1,0), Geometric::vector(-1,0,0), Geometric::vector(0,0,1), Geometric::vector(0,1,0));

    t.addTest("1",Test::EXPECT_EQ(s.base_point(M_PI_4,0), b));
    t.addTest("2",Test::EXPECT_EQ(s.base_point(M_PI_2,M_PI_2), b2));



    Planet s1 = Planet(Geometric::point0(), Geometric::vector(0,0,1), Geometric::point(1,0,0));
    Planet s2 = Planet(Geometric::point(5,0,0), Geometric::vector(0,0,1), Geometric::point(6,0,0));


    t.addTest("3",Test::EXPECT_EQ(collide(s1,M_PI,M_PI_2,s2,0,M_PI_2),true));
    t.addTest("4",Test::EXPECT_EQ(collide(s1,0,M_PI_2,s2,M_PI,M_PI_2),false));
    



    Planet s13 = Planet(Geometric::point(1,0,0),Geometric::vector(sqrt(2)/2,sqrt(2)/2,0),Geometric::point(1/sqrt(2)+1,-1/sqrt(2),0));
    Planet s23 = Planet(Geometric::point(6,5,0),Geometric::vector(sqrt(2),sqrt(2),0),Geometric::point(sqrt(2)+6,-sqrt(2)+5,0));

    t.addTest("5",Test::EXPECT_EQ(collide(s13,0,M_PI_2,s23,0,M_PI_2),true));   
    t.addTest("6",Test::EXPECT_EQ(collide(s13,0,M_PI_2,s23,0,M_PI),true));  
    t.addTest("7",Test::EXPECT_EQ(collide(s13,M_PI_2,M_PI_4,s23,0,M_PI),false));  


    Planet s3 = Planet(Geometric::point(-10,5,-1), Geometric::vector(-1,0,0), Geometric::point(-10-1/sqrt(2),5,-1-1/sqrt(2)));
    Planet s4 = Planet(Geometric::point(0,4,2),Geometric::vector(0,2,0), Geometric::point(-2/sqrt(3),4+2/sqrt(3),2+2/sqrt(3)));

    t.addTest("8",Test::EXPECT_EQ(collide(s3,M_PI,M_PI_2,s4,5*M_PI_4,M_PI_2),false));

    // Collide 
    return t.runAll();  
}
