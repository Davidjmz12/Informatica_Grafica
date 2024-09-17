/**
 * @file test_geometric.cpp
 * @brief File that tests the Geometric class
 *
 * This file contains all the tests that has been made
 * for the Geometric class.
*/
#include <math.h>

#include "test.hpp"
#include "geometric.hpp"

int main()
{
    Tests t = Tests("GEOMETRIC_TEST");

    Geometric p = Geometric::point(1,1,1);
    Geometric p_plus_v2 = Geometric::point(5,6,9.2);
    Geometric p_minus_v2 = Geometric::point(-3,-4,-7.2);
    Geometric e1 = Geometric::vector(1,0,0);
    Geometric e2 = Geometric::vector(0,1,0);
    Geometric e3 = Geometric::vector(0,0,1);
    Geometric v1 = Geometric::vector(1,1,1);
    Geometric v2 = Geometric::vector(4,5,8.2);
    float norm = v2.norm();
    Geometric v2_n = Geometric::vector(4/norm,5/norm,8.2/norm);
    Geometric e1_4 = Geometric::vector(4,0,0);
    Geometric v2_4_2 = Geometric::vector(16.8,21.0,34.44);
    Geometric v1xv2 = Geometric::vector((float)3.2,(float)-4.2,(float)1);

    Geometric v2_e1 = Geometric::vector(5,5,8.2);
    Geometric v2_e2 = Geometric::vector(4,6,8.2);
    Geometric v2_e3 = Geometric::vector(4,5,9.2);

    Geometric v2_minus_e1 = Geometric::vector(3,5,8.2);
    Geometric v2_minus_e2 = Geometric::vector(4,4,8.2);
    Geometric v2_minus_e3 = Geometric::vector(4,5,7.2);

    Geometric v1_copy = Geometric::vector(1,1,1);

    //Check the constructors and the is_point / is_vector methodes
    t.addTest(Test::EXPECT_EQ(p.is_point(), true)); //1
    t.addTest(Test::EXPECT_EQ(p.is_vector(), false)); //2
    t.addTest(Test::EXPECT_EQ(e1.is_point(), false)); //3
    t.addTest(Test::EXPECT_EQ(e1.is_vector(), true)); //4

    //Check the norm method
    t.addTest(Test::EXPECT_EQ(e1.norm(), (float)1.0)); //5
    t.addTest(Test::EXPECT_EQ(v1.norm(), (float)sqrt(3))); //6
    t.addTest(Test::EXPECT_EXC([&p] {p.norm();})); //7
 
    //Check the normalize method
    t.addTest(Test::EXPECT_EQ(e1_4.normalize(), Geometric::vector(1,0,0))); //8
    t.addTest(Test::EXPECT_EQ(v2.normalize(), v2_n)); //9
    t.addTest(Test::EXPECT_EXC([&p] {p.normalize();})); //10

    //Check the dot product
    t.addTest(Test::EXPECT_EQ(e1.dot(e2), (float)0)); //11
    t.addTest(Test::EXPECT_EQ(v1.dot(v2), (float)17.2)); //12
    t.addTest(Test::EXPECT_EXC([&p,&e1]{p.dot(e1);})); //13
    t.addTest(Test::EXPECT_EXC([&e1,&p]{e1.dot(p);})); //14
    t.addTest(Test::EXPECT_EXC([&p] {p.dot(p);})); //15

    //Check the cross product
    t.addTest(Test::EXPECT_EQ(e1.cross(e2), e3)); //16
    t.addTest(Test::EXPECT_EQ(e2.cross(e3), e1)); //17
    t.addTest(Test::EXPECT_EQ(e3.cross(e1), e2)); //18
    t.addTest(Test::EXPECT_EQ(e2.cross(e1), e3 * -1)); //19
    t.addTest(Test::EXPECT_EQ(e3.cross(e2), e1 * -1)); //20
    t.addTest(Test::EXPECT_EQ(e1.cross(e3), e2 * -1)); //21
    t.addTest(Test::EXPECT_EQ(v1.cross(v2), v1xv2)); //22
    t.addTest(Test::EXPECT_EXC([&e1,&p] {e1.cross(p);})); //23
    t.addTest(Test::EXPECT_EXC([&e1,&p] {p.cross(e1);})); //24
    t.addTest(Test::EXPECT_EXC([&p] {p.cross(p);})); //25

    //Check linearly_dependent
    t.addTest(Test::EXPECT_EQ(e1.linearly_dependent(e1_4),true)); //26
    t.addTest(Test::EXPECT_EQ(v2.linearly_dependent(v2_4_2),true)); //27
    t.addTest(Test::EXPECT_EQ(e1.linearly_dependent(v2),false)); //28
    t.addTest(Test::EXPECT_EQ(v2.linearly_dependent(v1),false)); //29
    t.addTest(Test::EXPECT_EXC([&p,&e1]{p.linearly_dependent(e1);})); //30
    t.addTest(Test::EXPECT_EXC([&e1,&p]{e1.linearly_dependent(p);})); //31
    t.addTest(Test::EXPECT_EXC([&p] {p.linearly_dependent(p);})); //32

    //Check is_base
    t.addTest(Test::EXPECT_EQ(e1.is_base(e2,e3),true)); //33
    t.addTest(Test::EXPECT_EQ(e3.is_base(e2*-1,e1),true)); //34
    t.addTest(Test::EXPECT_EQ(e1.is_base(e1_4,e3),false)); //35
    t.addTest(Test::EXPECT_EXC([&p,&e1,&e2]{p.is_base(e1,e2);})); //36
    t.addTest(Test::EXPECT_EXC([&p,&e1,&e2]{e1.is_base(p,e2);})); //37
    t.addTest(Test::EXPECT_EXC([&p,&e1,&e2]{e2.is_base(e1,p);})); //38
    t.addTest(Test::EXPECT_EXC([&p,&e1]{p.is_base(p,e1);})); //39
    t.addTest(Test::EXPECT_EXC([&p,&e1]{p.is_base(e1,p);})); //40
    t.addTest(Test::EXPECT_EXC([&p,&e1]{e1.is_base(p,p);})); //41
    t.addTest(Test::EXPECT_EXC([&p]{p.is_base(p,p);})); //42

    //Check operator+
    t.addTest(Test::EXPECT_EQ(v2+e1,v2_e1)); //43
    t.addTest(Test::EXPECT_EQ(v2+e2,v2_e2)); //44
    t.addTest(Test::EXPECT_EQ(v2+e3,v2_e3)); //45
    t.addTest(Test::EXPECT_EQ(p+v2,p_plus_v2)); //46
    t.addTest(Test::EXPECT_EQ(v2+p,p_plus_v2)); //47
    t.addTest(Test::EXPECT_EXC([&p]{p+p;})); //48

    //Check operator-
    t.addTest(Test::EXPECT_EQ(v2-e1,v2_minus_e1)); //49
    t.addTest(Test::EXPECT_EQ(v2-e2,v2_minus_e2)); //50
    t.addTest(Test::EXPECT_EQ(v2-e3,v2_minus_e3)); //51
    t.addTest(Test::EXPECT_EQ(p-v2,p_minus_v2)); //52
    t.addTest(Test::EXPECT_EXC([&v2, &p]{v2-p;})); //53

    //Check operator*
    t.addTest(Test::EXPECT_EQ(v2*4.2,v2_4_2)); //54
    t.addTest(Test::EXPECT_EXC([&p]{p*3;})); //55

    //Check operator/
    t.addTest(Test::EXPECT_EQ(v2_4_2/4.2,v2)); //56
    t.addTest(Test::EXPECT_EXC([&p]{p/3;})); //57
    t.addTest(Test::EXPECT_EXC([&v2]{v2/0;})); //58

    //Check operator=
    t.addTest(Test::EXPECT_EQ(v1==v1_copy,true)); //59
    t.addTest(Test::EXPECT_EQ(v1==v2,false)); //60
    t.addTest(Test::EXPECT_EQ(p==v1,false)); //61

    //Check operator[]
    t.addTest(Test::EXPECT_EQ(v2[0],(float)4)); //62
    t.addTest(Test::EXPECT_EQ(v2[1],(float)5)); //63
    t.addTest(Test::EXPECT_EQ(v2[2],(float)8.2)); //64
    t.addTest(Test::EXPECT_EXC([&v2]{v2[-1];})); //65
    t.addTest(Test::EXPECT_EXC([&v2]{v2[4];})); //66

    return t.runAll();
}