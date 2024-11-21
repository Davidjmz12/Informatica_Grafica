#pragma once

#include <array>
#include <string>
#include <memory>
#include <functional>

#include "color/colorRGB.hpp"
#include "color/CIE_1931_nvidia.hpp"

#ifdef SPECTRAL_COLOR
class Color{
private:

    static constexpr size_t SIZE = 32;

    std::array<double,SIZE> _channels{};

    static constexpr std::array<double, SIZE> WAVELENGTHS = {
        380.00, 392.90, 405.81, 418.71, 431.61, 444.52, 457.42, 470.32, 
        483.23, 496.13, 509.03, 521.94, 534.84, 547.74, 560.65, 573.55, 
        586.45, 599.35, 612.26, 625.16, 638.06, 650.97, 663.87, 676.77, 
        689.68, 702.58, 715.48, 728.39, 741.29, 754.19, 767.10, 780.00, 
    };  

    static constexpr double increment = 12.9;

public:
    
    Color();

    explicit Color(const std::array<double,32>& channels_32);

    explicit Color(const std::array<double,16>& channels_16);

    explicit Color(const std::array<double,8>& channels_8);

    explicit Color(const std::array<double,3>& rgb);

    explicit Color(const std::function<double(double)>& f);
    
    explicit Color(double intensity);

    [[nodiscard]] ColorRGB to_rgb() const;
    
    [[nodiscard]] Color apply_tone_mapping(const std::unique_ptr<ToneMapping>& t) const;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] double luminance_mean() const;

    [[nodiscard]] double luminance_max() const;


    double operator[](size_t index) const;

    Color operator+(const Color& c) const;
    Color operator*(const Color& c) const;
    Color operator*(double f) const;
    Color operator/(double f) const;

    friend std::ostream& operator<<(std::ostream& os, const Color& g);

    bool operator==(const Color& c) const;
    bool operator<=(double f) const;

};

#else

using Color = ColorRGB;

#endif  // SPECTRAL_COLOR

