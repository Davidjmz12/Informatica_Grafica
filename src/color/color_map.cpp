
#include "color/color_map.hpp"
#include <utility>

ColorMap::ColorMap()= default;

#ifdef SPECTRAL_COLOR
ColorMap::ColorMap(const MatrixSC& spectral_colors)
{
    MatrixRGB colors; // Vector to store the new colors
    for(const auto& i: spectral_colors)
    {
        std::vector<ColorRGB> colors_row; // Vector to store the new colors of the row
        for (Color color: i)
        {
            colors_row.push_back(color.to_rgb());
        }
        colors.push_back(colors_row);
    }
    this->_colors = colors;
}
#endif

ColorMap::ColorMap(MatrixRGB colors):
    _colors(std::move(colors))
{}

double ColorMap::max() const
{
    double max = 0;
    for(const auto& i: this->_colors)
    {
        for (ColorRGB color: i)
        {
            for(size_t j=0; j<3; ++j)
            {
                if(color[j]>max)
                {
                    max = color[j];
                }
            }
        }
    }
    return max;
}

ColorMap ColorMap::apply_tone_mapping(const std::unique_ptr<ToneMapping>& t, const size_t new_resolution) const
{

    MatrixRGB colors; // Vector to store the new colors
    for(const auto& i: this->_colors)
    {
        std::vector<ColorRGB> colors_row; // Vector to store the new colors of the row
        for (ColorRGB color: i)
        {
            colors_row.push_back(color.apply_tone_mapping(t, new_resolution));
        }
        colors.push_back(colors_row);
    }
    return ColorMap(colors);
}

MatrixRGB ColorMap::colors() const
{
    return this->_colors;
}

std::string ColorMap::to_string() const
{
    std::string s;
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

bool ColorMap::operator==(const ColorMap& l) const
{
    return(l.colors()==this->_colors);   // Compare the colors of the two ColorMap objects
}

std::ostream& operator<<(std::ostream& os,const ColorMap& g)
{
    os << std::setprecision(0) << std::fixed;
    os << g.to_string();

    return os;
}