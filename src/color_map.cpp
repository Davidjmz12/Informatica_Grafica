
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

ColorMap ColorMap::apply_tone_mapping(ToneMapping t) const
{
    ColorMap aux = this->RGB_to_HSV(); // Convert the colors to HSV
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
    return ColorMap(colors,HSV).HSV_to_RGB(); // Return the new ColorMap object with RGB colors.
}

vector<vector<Color>> ColorMap::colors() const
{
    return this->_colors;
}

bool ColorMap::operator==(ColorMap l) const
{
    return(l.colors()==this->_colors);   // Compare the colors of the two ColorMap objects
}

std::ostream& operator<<(std::ostream& os,const ColorMap& g)
{
    for (auto v: g.colors()) 
    {
        // Print each color in the row
        for (size_t i = 0; i < v.size(); ++i) 
        {
            os << v[i];
            if (i < v.size() - 1) 
                os << "\t";
        }
        os << "\n";
    } 

    return os;
}