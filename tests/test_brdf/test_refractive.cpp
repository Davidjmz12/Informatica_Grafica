
#include "test/test.hpp"
#include "properties/brdf/refractive_brdf.hpp"

int main()
{
    Tests t = Tests("REFRACTIVE BRDF TESTS");

    RefractiveBRDF r1 = RefractiveBRDF(Color(1), 1.5);
    Vector normal = Vector(0, 0, 1);
    Point int_point = Point(0, 0, 0);
    Vector w_0 = Vector(0, 1, 1).normalize();
    Ray r;
    double ref_co_entry = 1;

    bool sample = r1.sample_ray(w_0, int_point, normal, ref_co_entry, r, true);
    t.addTest("1", Test::EXPECT_EQ(sample, true));




}