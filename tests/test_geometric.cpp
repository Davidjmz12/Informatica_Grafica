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
    double norm = v2.norm();
    Geometric v2_n = Geometric::vector(4/norm,5/norm,8.2/norm);
    Geometric e1_4 = Geometric::vector(4,0,0);
    Geometric v2_4_2 = Geometric::vector(16.8,21.0,34.44);
    Geometric v1xv2 = Geometric::vector((double)3.2,(double)-4.2,(double)1);

    Geometric v2_e1 = Geometric::vector(5,5,8.2);
    Geometric v2_e2 = Geometric::vector(4,6,8.2);
    Geometric v2_e3 = Geometric::vector(4,5,9.2);

    Geometric v2_minus_e1 = Geometric::vector(3,5,8.2);
    Geometric v2_minus_e2 = Geometric::vector(4,4,8.2);
    Geometric v2_minus_e3 = Geometric::vector(4,5,7.2);

    Geometric v1_copy = Geometric::vector(1,1,1);

    //Check the constructors and the is_point / is_vector methods
    t.addTest("1", Test::EXPECT_EQ(p.is_point(), true)); //1
    t.addTest("2", Test::EXPECT_EQ(p.is_vector(), false)); //2
    t.addTest("3", Test::EXPECT_EQ(e1.is_point(), false)); //3
    t.addTest("4", Test::EXPECT_EQ(e1.is_vector(), true)); //4

    //Check the norm method
    t.addTest("5", Test::EXPECT_EQ(e1.norm(), (double)1.0)); //5
    t.addTest("6", Test::EXPECT_EQ(v1.norm(), (double)sqrt(3))); //6
    t.addTest("7", Test::EXPECT_EXC([&p] {p.norm();})); //7
 
    //Check the normalize method
    t.addTest("8", Test::EXPECT_EQ(e1_4.normalize(), Geometric::vector(1,0,0))); //8
    t.addTest("9", Test::EXPECT_EQ(v2.normalize(), v2_n)); //9
    t.addTest("10", Test::EXPECT_EXC([&p] {p.normalize();})); //10

    //Check the dot product
    t.addTest("11", Test::EXPECT_EQ(e1.dot(e2), (double)0)); //11
    t.addTest("12", Test::EXPECT_EQ(v1.dot(v2), (double)17.2)); //12
    t.addTest("13", Test::EXPECT_EXC([&p,&e1]{p.dot(e1);})); //13
    t.addTest("14", Test::EXPECT_EXC([&e1,&p]{e1.dot(p);})); //14
    t.addTest("15", Test::EXPECT_EXC([&p] {p.dot(p);})); //15

    //Check the cross product
    t.addTest("16", Test::EXPECT_EQ(e1.cross(e2), e3)); //16
    t.addTest("17", Test::EXPECT_EQ(e2.cross(e3), e1)); //17
    t.addTest("18", Test::EXPECT_EQ(e3.cross(e1), e2)); //18
    t.addTest("19", Test::EXPECT_EQ(e2.cross(e1), e3 * -1)); //19
    t.addTest("20", Test::EXPECT_EQ(e3.cross(e2), e1 * -1)); //20
    t.addTest("21", Test::EXPECT_EQ(e1.cross(e3), e2 * -1)); //21
    t.addTest("22", Test::EXPECT_EQ(v1.cross(v2), v1xv2)); //22
    t.addTest("23", Test::EXPECT_EXC([&e1,&p] {e1.cross(p);})); //23
    t.addTest("24", Test::EXPECT_EXC([&e1,&p] {p.cross(e1);})); //24
    t.addTest("25", Test::EXPECT_EXC([&p] {p.cross(p);})); //25

    //Check linearly_dependent
    t.addTest("26", Test::EXPECT_EQ(e1.linearly_dependent(e1_4),true));
    t.addTest("27", Test::EXPECT_EQ(v2.linearly_dependent(v2_4_2),true)); //27
    t.addTest("28", Test::EXPECT_EQ(e1.linearly_dependent(v2),false)); //28
    t.addTest("29", Test::EXPECT_EQ(v2.linearly_dependent(v1),false)); //29
    t.addTest("30", Test::EXPECT_EXC([&p,&e1]{p.linearly_dependent(e1);})); //30
    t.addTest("31", Test::EXPECT_EXC([&e1,&p]{e1.linearly_dependent(p);})); //31
    t.addTest("32", Test::EXPECT_EXC([&p] {p.linearly_dependent(p);})); //32

    //Check is_base
    t.addTest("33", Test::EXPECT_EQ(e1.is_base(e2,e3),true)); //33
    t.addTest("34", Test::EXPECT_EQ(e3.is_base(e2*-1,e1),true)); //34
    t.addTest("35", Test::EXPECT_EQ(e1.is_base(e1_4,e3),false)); //35
    t.addTest("36", Test::EXPECT_EXC([&p,&e1,&e2]{p.is_base(e1,e2);})); //36
    t.addTest("37", Test::EXPECT_EXC([&p,&e1,&e2]{e1.is_base(p,e2);})); //37
    t.addTest("38", Test::EXPECT_EXC([&p,&e1,&e2]{e2.is_base(e1,p);})); //38
    t.addTest("39", Test::EXPECT_EXC([&p,&e1]{p.is_base(p,e1);})); //39
    t.addTest("40", Test::EXPECT_EXC([&p,&e1]{p.is_base(e1,p);})); //40
    t.addTest("41", Test::EXPECT_EXC([&p,&e1]{e1.is_base(p,p);})); //41
    t.addTest("42", Test::EXPECT_EXC([&p]{p.is_base(p,p);})); //42

    //Check operator+
    t.addTest("43", Test::EXPECT_EQ(v2+e1,v2_e1)); //43
    t.addTest("44", Test::EXPECT_EQ(v2+e2,v2_e2)); //44
    t.addTest("45", Test::EXPECT_EQ(v2+e3,v2_e3)); //45
    t.addTest("46", Test::EXPECT_EQ(p+v2,p_plus_v2)); //46
    t.addTest("47", Test::EXPECT_EQ(v2+p,p_plus_v2)); //47
    t.addTest("48", Test::EXPECT_EXC([&p]{p+p;})); //48

    //Check operator-
    t.addTest("49", Test::EXPECT_EQ(v2-e1,v2_minus_e1)); //49
    t.addTest("50", Test::EXPECT_EQ(v2-e2,v2_minus_e2)); //50
    t.addTest("51", Test::EXPECT_EQ(v2-e3,v2_minus_e3)); //51
    t.addTest("52", Test::EXPECT_EQ(p-v2,p_minus_v2)); //52
    t.addTest("53", Test::EXPECT_EXC([&v2, &p]{v2-p;})); //53

    //Check operator*
    t.addTest("54", Test::EXPECT_EQ(v2*4.2,v2_4_2)); //54
    t.addTest("55", Test::EXPECT_EXC([&p]{p*3;})); //55

    //Check operator/
    t.addTest("56", Test::EXPECT_EQ(v2_4_2/4.2,v2)); //56
    t.addTest("57", Test::EXPECT_EXC([&p]{p/3;})); //57
    t.addTest("58", Test::EXPECT_EXC([&v2]{v2/0;})); //58

    //Check operator=
    t.addTest("59", Test::EXPECT_EQ(v1==v1_copy,true)); //59
    t.addTest("60", Test::EXPECT_EQ(v1==v2,false)); //60
    t.addTest("61", Test::EXPECT_EQ(p==v1,false)); //61

    //Check operator[]
    t.addTest("62", Test::EXPECT_EQ(v2[0],(double)4)); //62
    t.addTest("63", Test::EXPECT_EQ(v2[1],(double)5)); //63
    t.addTest("64", Test::EXPECT_EQ(v2[2],(double)8.2)); //64
    t.addTest("65", Test::EXPECT_EXC([&v2]{v2[-1];})); //65
    t.addTest("66", Test::EXPECT_EXC([&v2]{v2[4];})); //66

    return t.runAll();
}