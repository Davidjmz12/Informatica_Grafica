
#include "color_map.hpp"

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
    if(this->_encode == HSV)
    {
        return (*this);
    }

    vector<vector<Color>> colors;
    for(auto v: this->_colors)
    {
        vector<Color> colors_row;
        for (Color color: v)
        {
            colors_row.push_back(color.RGB_to_HSV());
        }
        colors.push_back(colors_row);
    }    

    return ColorMap(colors,HSV);

}

ColorMap ColorMap::HSV_to_RGB() const
{
    if(this->_encode == RGB)
    {
        return (*this);
    }
    
    vector<vector<Color>> colors;
    for(auto i: this->_colors)
    {
        vector<Color> colors_row;
        for (Color color: i)
        {
            colors_row.push_back(color.HSV_to_RGB());
        }
        colors.push_back(colors_row);
    }    

    return ColorMap(colors,RGB);
}

vector<vector<Color>> ColorMap::colors() const
{
    return this->_colors;
}

bool ColorMap::operator==(ColorMap l) const
{
    return(l.colors()==this->_colors);  
}

std::ostream& operator<<(std::ostream& os,const ColorMap& g)
{
    for (auto v: g.colors()) 
    {
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