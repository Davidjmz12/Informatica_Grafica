#pragma once

#include "brdf.hpp"

/**
 * @brief Class that represents the diffuse property of
 * an object
 */
class DiffuseBRDF : public BRDF
{
private:
    SpectralColor _k; // The color of the object

public:
    DiffuseBRDF(SpectralColor k);

    DiffuseBRDF();
    
    SpectralColor eval(Point p, Vector v, Vector w0) const override;

    std::string to_string() const override;

    friend std::ostream& operator<<(std::ostream& os, const DiffuseBRDF& d);
};
