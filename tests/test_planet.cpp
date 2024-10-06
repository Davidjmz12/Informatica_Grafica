#include <math.h>

#include "test.hpp"
#include "planet.hpp"

int main()
{
    Tests t = Tests("TESTS planet");

    Planet s = Planet(Point(), Vector(0,0,1), Point(1,0,0));
    Base b = Base(Point(1/sqrt(2),0,1/sqrt(2)), Vector(0,1,0), Vector(-1/sqrt(2),0,1/sqrt(2)), Vector(1/sqrt(2),0,1/sqrt(2)));
    Base b2 = Base(Point(0,1,0), Vector(-1,0,0), Vector(0,0,1), Vector(0,1,0));

    t.addTest("1",Test::EXPECT_EQ(s.base_point(M_PI_4,0), b));
    t.addTest("2",Test::EXPECT_EQ(s.base_point(M_PI_2,M_PI_2), b2));



    Planet s1 = Planet(Point(), Vector(0,0,1), Point(1,0,0));
    Planet s2 = Planet(Point(5,0,0), Vector(0,0,1), Point(6,0,0));


    t.addTest("3",Test::EXPECT_EQ(collide(s1,M_PI,M_PI_2,s2,0,M_PI_2),true));
    t.addTest("4",Test::EXPECT_EQ(collide(s1,0,M_PI_2,s2,M_PI,M_PI_2),false));


    Planet s13 = Planet(Point(1,0,0),Vector(sqrt(2)/2,sqrt(2)/2,0),Point(1/sqrt(2)+1,-1/sqrt(2),0));
    Planet s23 = Planet(Point(6,5,0),Vector(sqrt(2),sqrt(2),0),Point(sqrt(2)+6,-sqrt(2)+5,0));

    t.addTest("5",Test::EXPECT_EQ(collide(s13,0,M_PI_2,s23,0,M_PI_2),true));   
    //t.addTest("6",Test::EXPECT_EQ(collide(s13,0,M_PI_2,s23,0,M_PI),true));  
    //t.addTest("7",Test::EXPECT_EQ(collide(s13,M_PI_2,M_PI_4,s23,0,M_PI),false));  


    Planet s3 = Planet(Point(-10,5,-1), Vector(-1,0,0), Point(-10-1/sqrt(2),5,-1-1/sqrt(2)));
    Planet s4 = Planet(Point(0,4,2),Vector(0,2,0), Point(-2/sqrt(3),4+2/sqrt(3),2+2/sqrt(3)));

    //t.addTest("8",Test::EXPECT_EQ(collide(s3,M_PI,M_PI_2,s4,5*M_PI_4,M_PI_2),false));

    // Collide 

    Planet p5 = Planet(Point(5,6,7),Vector(3,0,0),Point(5,6,10));
    Base b3 = Base(Point(5,6,4),Vector(0,1,0),Vector(1,0,0),Vector(0,0,-1));

    t.addTest("9",Test::EXPECT_EQ(p5.base_point(M_PI_2,M_PI), b3));
    return t.runAll();  
}
