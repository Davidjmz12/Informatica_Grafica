#pragma once

#include "brdf.hpp"

/**
 * @brief Class that represents the diffuse property of
 * an object
 */
class DiffuseBRDF : public BRDF
{
private:
    Color _k; // The color of the object

public:
    DiffuseBRDF(Color k);

    DiffuseBRDF();
    
    Color eval(Point p, Vector v, Vector w0) const override;
};
