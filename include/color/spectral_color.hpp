#pragma once

#include <array>
#include <string>
#include <memory>
#include <functional>

#include "color/colorRGB.hpp"
#include "color/CIE_1931_nvidia.hpp"

using SC3 = std::array<double,3>;
using SC8 = std::array<double,8>;
using SC16 = std::array<double,16>;
using SC32 = std::array<double,32>;

class SpectralColor{
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
    
    SpectralColor();

    explicit SpectralColor(const std::array<double,32>& channels_32);

    explicit SpectralColor(const std::array<double,16>& channels_16);

    explicit SpectralColor(const std::array<double,8>& channels_8);

    explicit SpectralColor(const std::array<double,3>& rgb);

    explicit SpectralColor(const std::function<double(double)>& f);
    
    explicit SpectralColor(double intensity);

    [[nodiscard]] ColorRGB to_rgb() const;
    
    [[nodiscard]] SpectralColor apply_tone_mapping(const std::unique_ptr<ToneMapping>& t) const;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] double luminance_mean() const;

    [[nodiscard]] double luminance_max() const;


    double operator[](size_t index) const;

    SpectralColor operator+(const SpectralColor& c) const;
    SpectralColor operator*(const SpectralColor& c) const;
    SpectralColor operator*(double f) const;
    SpectralColor operator/(double f) const;

    friend std::ostream& operator<<(std::ostream& os, const SpectralColor& g);

    bool operator==(const SpectralColor& c) const;
    bool operator<=(double f) const;

};