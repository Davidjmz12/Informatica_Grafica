/**
 * @file color_map.hpp
 * @brief Implementation of the ColorMap header.
 * @authors Davidjmz12 DavidTizne
 * @date 01/10/2024
 *
 * This file contains the implementation of the ColorMap class, which represents
 * a 2D map of colors.
*/

#include "color_map.hpp"


ColorMap::ColorMap(){}

ColorMap::ColorMap(vector<vector<Color>> colors, ColorEncoding encode)
{
    for(auto v: colors)
    {
        for (Color color: v)
        {
            if(color.get_type() != encode)
            {
                throw std::invalid_argument("All colors must be equally encoded");
            }
        }
    } 
    this->_colors = colors;
    this->_encode = encode;
}


ColorMap ColorMap::change_range(std::array<double,3> factor) const
{
    vector<vector<Color>> colors; // Vector to store the new colors
    for(auto v: this->_colors)
    {
        vector<Color> colors_row; // Vector to store the new colors of the row
        for (Color color: v)
        {
            colors_row.push_back(color.change_range(factor));
        }
        colors.push_back(colors_row);
    }   
    return ColorMap(colors,this->_encode);
}


ColorMap ColorMap::RGB_to_HSV() const
{
    // If the colors are already in HSV, return the same object
    if(this->_encode == HSV)
    {
        return (*this);
    }

    vector<vector<Color>> colors; // Vector to store the new colors
    for(auto v: this->_colors)
    {
        vector<Color> colors_row; // Vector to store the new colors of the row
        for (Color color: v)
        {
            colors_row.push_back(color.RGB_to_HSV());
        }
        colors.push_back(colors_row);
    }    

    // Return the new ColorMap object with HSV colors.
    return ColorMap(colors,HSV);

}

ColorMap ColorMap::HSV_to_RGB() const
{
    // If the colors are already in RGB, return the same object
    if(this->_encode == RGB)
    {
        return (*this);
    }
    
    vector<vector<Color>> colors; // Vector to store the new colors
    for(auto i: this->_colors)
    {
        vector<Color> colors_row; // Vector to store the new colors of the row
        for (Color color: i)
        {
            colors_row.push_back(color.HSV_to_RGB());
        }
        colors.push_back(colors_row);
    }    

    // Return the new ColorMap object with RGB colors.
    return ColorMap(colors,RGB);
}

ColorMap ColorMap::apply_tone_mapping(ToneMapping* t) const
{
    // RGB [0,t.max_luminance()]
    ColorMap aux = this->RGB_to_HSV(); // Convert the colors to HSV
    aux = aux.change_range({6,1,t->max_luminance()}); 

    vector<vector<Color>> colors; // Vector to store the new colors
    for(auto i: aux.colors())
    {
        vector<Color> colors_row; // Vector to store the new colors of the row
        for (Color color: i)
        {
            colors_row.push_back(color.apply_tone_mapping(t));
        }
        colors.push_back(colors_row);
    }
    aux = ColorMap(colors,HSV).HSV_to_RGB().change_range(Color::same_range(t->max_luminance()));
    return aux; // Return the new ColorMap object with RGB colors.
}

ColorMap ColorMap::normalize() const
{
    vector<vector<Color>> colors; // Vector to store the new colors
    for(auto i: this->_colors)
    {
        vector<Color> colors_row; // Vector to store the new colors of the row
        for (Color color: i)
        {
            colors_row.push_back(color.normalize());
        }
        colors.push_back(colors_row);
    }    

    // Return the new ColorMap object with normalized colors.
    return ColorMap(colors,this->_encode);
}

vector<vector<Color>> ColorMap::colors() const
{
    return this->_colors;
}

Color ColorMap::get_rgb(int row, int col) const
{
    return this->_colors[row][col];
}

bool ColorMap::operator==(ColorMap l) const
{
    return(l.colors()==this->_colors);   // Compare the colors of the two ColorMap objects
}

std::ostream& operator<<(std::ostream& os,const ColorMap& g)
{
    auto g_c = g.colors();
    os << std::setprecision(0) << std::fixed;
    for (size_t i = 0; i < g_c.size(); ++i) 
    {
        auto v = g_c[i];
        // Print each color in the row
        for (size_t j = 0; j < v.size(); ++j) 
        {
            os << v[j];
            if (j < v.size() - 1) 
                os << "\t";
        }
        if (i < g_c.size() - 1) 
            os << std::endl;
    } 

    return os;
}