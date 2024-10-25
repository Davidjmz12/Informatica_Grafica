/**
 * @file color_map.hpp
 * @brief Implementation of the ColorMap header.
 * @authors Davidjmz12 DavidTizne
 * @date 01/10/2024
 *
 * This file contains the implementation of the ColorMap class, which represents
 * a 2D map of colors.
*/

#include "color/color_map.hpp"


ColorMap::ColorMap(){}

ColorMap::ColorMap(vector<vector<SpectralColor>> colors):
    _colors(colors)
{}


ColorMap ColorMap::apply_tone_mapping(ToneMapping* t) const
{

    vector<vector<SpectralColor>> colors; // Vector to store the new colors
    for(auto i: this->_colors)
    {
        vector<SpectralColor> colors_row; // Vector to store the new colors of the row
        for (SpectralColor color: i)
        {
            colors_row.push_back(color.apply_tone_mapping(t));
        }
        colors.push_back(colors_row);
    }
    return ColorMap(colors);
}

vector<vector<SpectralColor>> ColorMap::colors() const
{
    return this->_colors;
}

std::string ColorMap::to_string() const
{
    std::string s = "";
    for (size_t i = 0; i < this->_colors.size(); ++i) 
    {
        auto v = this->_colors[i];
        // Print each color in the row
        for (size_t j = 0; j < v.size(); ++j) 
        {
            s += v[j].to_string();
            if (j < v.size() - 1) 
                s += "\t";
        }
        if (i < this->_colors.size() - 1) 
            s += "\n";
    } 

    return s;
}

bool ColorMap::operator==(ColorMap l) const
{
    return(l.colors()==this->_colors);   // Compare the colors of the two ColorMap objects
}

std::ostream& operator<<(std::ostream& os,const ColorMap& g)
{
    os << std::setprecision(0) << std::fixed;
    os << g.to_string();

    return os;
}