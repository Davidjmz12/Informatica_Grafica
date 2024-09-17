/**
 * @file test_matrix.cpp
 * @brief File that tests the Matrix class
 *
 * This file contains all the tests that has been made
 * for the Matrix class.
*/

#include "test.hpp"
#include "matrix.hpp"

int main()
{    
    Tests t = Tests("MATRIX TESTS");

    // GET METHOD: TEST 1-4
    float m1f[4][4] =    {  { 1, 2, 3, 4},
                            { 5, 6, 7, 8},
                            {-8,-7,-6,-5},
                            {-4,-3,-2,-1}
                        };
    Matrix4x4 m1 = Matrix4x4(m1f);

    t.addTest(Test::EXPECT_EQ(m1.get(0,0),(float)1));
    t.addTest(Test::EXPECT_EQ(m1.get(2,3),(float)-5));
    t.addTest(Test::EXPECT_EXC([&m1] { m1.get(8,2); } ));
    t.addTest(Test::EXPECT_EXC([&m1] { m1.get(2,-1); } ));

    // INVERSE METHOD: TEST 5-8
    float m2f[4][4] =    {  { 2, 0, 0, 0},
                            { 0,-4, 0, 0},
                            { 0, 0,0.2,0},
                            { 0, 0, 0, -0.1}
                        };
    Matrix4x4 m2 = Matrix4x4(m2f);

    float m2fi[4][4] =    { { 0.5, 0, 0, 0},
                            { 0,-0.25, 0, 0},
                            { 0, 0, 5,0},
                            { 0, 0, 0, -10}
                        };
    Matrix4x4 m2i = Matrix4x4(m2fi);

    float m3f[4][4] =    {  { 1, 0, 0, 4},
                            { 0, 1, 0, 8},
                            { 0, 0, 1, -3.2},
                            { 0, 0, 0, 1}
                        };
    Matrix4x4 m3 = Matrix4x4(m3f);

    float m3fi[4][4] =    { { 1, 0, 0, -4},
                            { 0, 1, 0, -8},
                            { 0, 0, 1, 3.2},
                            { 0, 0, 0, 1}
                        };
    Matrix4x4 m3i = Matrix4x4(m3fi);

    float m4f[4][4] =    { { 2, 4, 0, 7},
                            { 1, 5, 0, 7.0/2},
                            {-2, 0,-4,-7},
                            { 2, 2, 4, 8}
                        };
    Matrix4x4 m4 = Matrix4x4(m4f);

    float m4fi[4][4] =    { { -1.0/3, 5.0/3, -7.0/2, -7.0/2},
                            { -1.0/6, 1.0/3, 0, 0},
                            { -5.0/12, 1.0/3, -1.0/4, 0},
                            { 1.0/3, -2.0/3, 1, 1}
                        };
    Matrix4x4 m4i = Matrix4x4(m4fi);

    float m5f[4][4] =    {  { 2, 3, 4, 5},
                            { 0, 2, -4, -1},
                            { 1, 2, 3, 4},
                            { 1, 1, 1, 1}
                        };
    Matrix4x4 m5 = Matrix4x4(m5f);

    t.addTest(Test::EXPECT_EQ(m2.inverse(),m2i));
    t.addTest(Test::EXPECT_EQ(m3.inverse(),m3i));
    t.addTest(Test::EXPECT_EQ(m4.inverse(),m4i));
    t.addTest(Test::EXPECT_EXC([&m5] { m5.inverse(); }));


    // DETERMINANT METHOD: TEST 9-11
    t.addTest(Test::EXPECT_EQ(Matrix4x4::identity().determinant(), (float)1));
    t.addTest(Test::EXPECT_EQ(m4.determinant(), (float)-24));
    t.addTest(Test::EXPECT_EQ(m5.determinant(), (float)0));

    // OPERATOR * MATRICES TEST 12-13
    t.addTest(Test::EXPECT_EQ(m3*Matrix4x4::identity(), m3));
    t.addTest(Test::EXPECT_EQ(m4*m4i, Matrix4x4::identity()));

    // OPERATOR * GEOMETRIC TEST 14
    Geometric g = Geometric::vector(-2,1.0/2,3.0/2);

    t.addTest(Test::EXPECT_EQ(m5*g,Geometric::vector(7.0/2,-5,7.0/2)));


    t.runAll();

    return 0;
}