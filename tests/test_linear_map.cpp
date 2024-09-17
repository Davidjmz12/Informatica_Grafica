/**
 * @file test_linear_map.cpp
 * @brief File that tests the Linear_Map class
 *
 * This file contains all the tests that has been made
 * for the Linear_Map class.
*/

#include <math.h>

#include "test.hpp"
#include "linear_map.hpp"
#include "base.hpp"
#include "geometric.hpp"

int main()
{
    Tests t = Tests("LINEAR_MAP_TEST");

    // Change of basis
    Base id= Base::canonic_base();
    t.addTest(Test::EXPECT_EQ(Linear_Map::change_basis(id,id),Linear_Map::identity()));
    Base b1 = Base(Geometric::point(1,1,1),Geometric::vector(1,0,0),
                   Geometric::vector(0,1,0),Geometric::vector(0,0,1));
    Base b2 = Base(Geometric::point(2,2,2),Geometric::vector(2,1,0),
                   Geometric::vector(0,1,2),Geometric::vector(2,0,1));

    float m[4][4] = {{1/6.0 , 4/6.0 , -2/6.0, -3/6.0},
                               {-1/6.0, 2/6.0 , 2/6.0 , -3/6.0},
                               {2/6.0 , -4/6.0, 2/6.0 , 0     },
                               {0     , 0     , 0     , 1     }};
    Linear_Map res=Linear_Map(m);
    t.addTest(Test::EXPECT_EQ(Linear_Map::change_basis(b1,b2),res));

    // Constructors rotation
    Geometric v = Geometric::vector(1,2,1);
    Geometric v_inv = Geometric::vector(-1,-2,-1);
    Linear_Map rot = Linear_Map::rotation(v,M_PI_2);
    Linear_Map rot_inv = Linear_Map::rotation(v_inv,M_PI_2);
    Linear_Map rot2 = Linear_Map::rotation(v,M_PI*3/2);

    t.addTest(Test::EXPECT_EQ(rot*rot_inv,Linear_Map::identity()));
    t.addTest(Test::EXPECT_EQ(rot*rot2,Linear_Map::identity()));

    // Constructors scale
    float a[3] = {1.0,2.0,3.0}; float b[3] = {1,1.0/2.0,1/3.0};
    Linear_Map scale= Linear_Map::scale(a);
    Linear_Map scale_inv = Linear_Map::scale(b);

    t.addTest(Test::EXPECT_EQ(scale*scale_inv,Linear_Map::identity()));

    // Constructors translation
    Linear_Map tras= Linear_Map::translation(v);
    Linear_Map tras_inv = Linear_Map::translation(v_inv);
    t.addTest(Test::EXPECT_EQ(tras*tras_inv,Linear_Map::identity()));

    // Inverse
    t.addTest(Test::EXPECT_EQ(tras.inverse(),tras_inv));
    t.addTest(Test::EXPECT_EQ(scale.inverse(),scale_inv));

    // LT times Geometric
    t.addTest(Test::EXPECT_EQ(rot*v,v));
    t.addTest(Test::EXPECT_EQ(rot*(v*2),v*2));

    t.runAll();

    return 0;
}