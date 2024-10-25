#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "color/colorRGB.hpp"
#include "color/CIE_1931_nvidia.hpp"

class SpectralColor{
private:

    std::vector<double> _chanels;
    std::vector<double> _wave_lengths;
    size_t _size;

    double get_increment(size_t i) const;


public:
    
    SpectralColor();

    SpectralColor(std::vector<double> chanels);

    SpectralColor(std::vector<double> chanels, std::vector<double> wave_lengths);

    static SpectralColor from_rgb(std::array<double,3> rgb);

    std::vector<double> get_wave_lengths() const;

    ColorRGB to_rgb() const;
    
    SpectralColor apply_tone_mapping(ToneMapping* t) const;

    std::string to_string() const;


    double operator[](int index) const;

    SpectralColor operator+(SpectralColor c) const;
    SpectralColor operator*(SpectralColor c) const;
    SpectralColor operator*(double f) const;
    SpectralColor operator/(double f) const;

    friend std::ostream& operator<<(std::ostream& os, const SpectralColor& g);

    bool operator==(SpectralColor c) const;

};