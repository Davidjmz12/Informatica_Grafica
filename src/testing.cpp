#include "metrics/metrics.hpp"
#include "color/spectral_color.hpp"


int main()
{
    SpectralColor c1 = SpectralColor(SC3{0.5, 0.5, 0.5});
    std::cout << c1.to_rgb() << std::endl;
}

