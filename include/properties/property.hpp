#pragma once

#include <memory>

#include "color/color.hpp"
#include "properties/brdf/diffuse_brdf.hpp"

class BRDF;

class Property
{
private:
    std::shared_ptr<BRDF> _brdf;
public:

    Property();
    Property(std::shared_ptr<BRDF> brdf);

    Color get_color() const;
    BRDF* get_BRDF() const;

    friend std::ostream& operator<<(std::ostream& os, const Property& p);

    std::string to_string() const;

};
