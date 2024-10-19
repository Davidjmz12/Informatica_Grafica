/**
 * @file test_linear_map.cpp
 * @brief File that tests the LinearMap class
 *
 * This file contains all the tests that has been made
 * for the LinearMap class.
*/

#include <math.h>

#include "test.hpp"
#include "linear_map.hpp"
#include "base.hpp"

int main()
{
    Tests t = Tests("LINEAR_MAP_TEST");

    // Change of basis
    Base id= Base::canonic_base();
    t.addTest("1",Test::EXPECT_EQ(LinearMap::change_basis(id,id),LinearMap::identity()));
    Base b1 = Base(Point(1,1,1),Vector(1,0,0),
                   Vector(0,1,0),Vector(0,0,1));
    Base b2 = Base(Point(2,2,2),Vector(2,1,0),
                   Vector(0,1,2),Vector(2,0,1));

    double m[4][4] = {{1/6.0 , 4/6.0 , -2/6.0, -3/6.0},
                               {-1/6.0, 2/6.0 , 2/6.0 , -3/6.0},
                               {2/6.0 , -4/6.0, 2/6.0 , 0     },
                               {0     , 0     , 0     , 1     }};
    LinearMap res=LinearMap(m);
    t.addTest("2",Test::EXPECT_EQ(LinearMap::change_basis(b1,b2),res));

    // Constructors rotation
    Vector v = Vector(1,2,1);
    Vector v_inv = Vector(-1,-2,-1);
    LinearMap rot = LinearMap::rotation(v,M_PI_2);
    LinearMap rot_inv = LinearMap::rotation(v_inv,M_PI_2);
    LinearMap rot2 = LinearMap::rotation(v,M_PI*3/2);

    t.addTest("3",Test::EXPECT_EQ(rot*rot_inv,LinearMap::identity()));
    t.addTest("4",Test::EXPECT_EQ(rot*rot2,LinearMap::identity()));

    // Constructors scale
    double a[3] = {1.0,2.0,3.0}; double b[3] = {1,1.0/2.0,1/3.0};
    LinearMap scale= LinearMap::scale(a);
    LinearMap scale_inv = LinearMap::scale(b);

    t.addTest("5",Test::EXPECT_EQ(scale*scale_inv,LinearMap::identity()));

    // Constructors translation
    LinearMap tras= LinearMap::translation(v);
    LinearMap tras_inv = LinearMap::translation(v_inv);
    t.addTest("6",Test::EXPECT_EQ(tras*tras_inv,LinearMap::identity()));

    // Inverse
    t.addTest("7",Test::EXPECT_EQ(tras.inverse(),tras_inv));
    t.addTest("8",Test::EXPECT_EQ(scale.inverse(),scale_inv));

    // LT times Geometric
    SpatialElement* v2 = new Vector(1,2,1);
    t.addTest("9",Test::EXPECT_EQ(Point(rot*v2),Point(v2)));
    SpatialElement* v3 = new Vector(2,4,2);
    t.addTest("10",Test::EXPECT_EQ(Point(rot*v3),Point(v3)));

    SpatialElement* p0 = new Point();
    t.addTest("11", Test::EXPECT_EQ(Vector(tras*p0), v));  

    
    return t.runAll();
}