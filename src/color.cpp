

#include "color.hpp"

const std::array<float, 3> Color::RGB_STANDARD_RANGE = {1.0f, 1.0f, 1.0f};
const std::array<float, 3> Color::HSV_STANDARD_RANGE = {6.0f, 1.0f, 1.0f};


Color::Color(std::array<float, 3> colors, std::array<float, 3> range , ColorEncoding type)
{

    if(colors[0]<0 || colors[0]>range[0] || colors[1]<0 || colors[1]>range[1] || colors[2]<0 || colors[2]>range[2])
    {
        throw std::invalid_argument("Color components of RGB must be between 0 and " + 
                                    std::to_string(RANGE_RGB));
    }
    
    this->_colors = colors;
    this->_range = range;
    this->_type = type;
};

Color Color::normalize() const
{
    std::array<float, 3> normalized_colors;
    std::array<float, 3> standard_range = this->_type == RGB ? RGB_STANDARD_RANGE : HSV_STANDARD_RANGE;
    for(unsigned int i=0; i<3; ++i)
    {
        normalized_colors[i] = this->_colors[i]*standard_range[i]/this->_range[i];
    }

    return Color(normalized_colors, standard_range, this->_type);
}

Color Color::change_range(std::array<float, 3> new_range) const
{
    std::array<float, 3> new_colors;
    for(unsigned int i=0; i<3; ++i)
    {
        new_colors[i] = this->_colors[i]*new_range[i]/this->_range[i];
    }

    return Color(new_colors, new_range, this->_type);
}

float Color::operator[](int index) const
{
    if(index<0 || index>2)
    {
        throw std::out_of_range("Invalid index for color component");
    }
    return this->_colors[index];
}

float Color::max() const
{
    float aux = this->_colors[0];

    for(unsigned int i=1; i<3; ++i)
    {
        if(this->_colors[i]>aux)
        {
            aux = this->_colors[i];
        }
    }
    return aux;
}

float Color::min() const
{
    float aux = this->_colors[0];

    for(unsigned int i=1; i<3; ++i)
    {
        if(this->_colors[i]<aux)
        {
            aux = this->_colors[i];
        }
    }
    return aux;
}

Color Color::RGB_to_HSV() const
{

    if(this->_type == HSV)
    {
        return (*this);
    }

    Color norm = this->normalize();

    float R = norm._colors[0];
    float G = norm._colors[1];
    float B = norm._colors[2];

    float max_col = norm.max();
    float min_col = norm.min();
    float dif = max_col-min_col;

    float H,S,V;

    if(dif == 0)
    {
        H = 0;
    } else if (max_col == R)
    {
        H = (G-B)/dif;
    } else if (max_col == G)
    {
        H = ((B-R)/dif+2);
    } else if (max_col == B)
    {
        H = ((R-G)/dif+4);
    }
    
    if(H<0)
    {
        H = fmod(H,6)+6;
    } else 
    {
        H = fmod(H,6);
    }

    
    V = max_col;
    
    if(V==0)
    {
        S = 0;
    } else 
    {
        S = dif/V;
    }

    return Color({H,S,V},HSV_STANDARD_RANGE,HSV);
}

Color Color::HSV_to_RGB() const
{

    if(this->_type == RGB)
    {
        return (*this);
    }

    Color norm = this->normalize();

    float H,S,V;
    H = norm._colors[0];
    S = norm._colors[1];
    V = norm._colors[2];

    float C = V*S;
    float X = C*(1-fabs(fmod(H,2)-1));
    float m = V-C;

    float R,G,B;

    R = m;
    G = m;
    B = m;

    if(0<=H && H<1)
    {
        R += C;
        G += X;
    } else if(1<=H && H<2)
    {
        R += X;
        G += C;
    } else if(2<=H && H<3)
    {
        G += C;
        B += X;
    } else if(3<=H && H<4)
    {
        G += X;
        B += C;
    } else if(4<=H && H<5)
    {
        R += X;
        B += C;
    } else
    {
        R += C;
        B += X;
    }

    return Color({R,G,B}, RGB_STANDARD_RANGE, RGB);
}

ColorEncoding Color::get_type() const
{
    return this->_type;
}

Color Color::apply_tone_mapping(ToneMapping t) const
{
    if(this->_type == RGB)
    {
        std::array<float, 3> max_values = {t.getMax(), t.getMax(), t.getMax()};
        if(max_values != this->_range)
            throw std::invalid_argument("Tone mapping maximum value must be equal to range of RGB colors ");

        return Color({t.evaluate((*this)[0]),t.evaluate((*this)[1]),t.evaluate((*this)[2])}, RGB_STANDARD_RANGE, RGB);
    }
    else 
    {
        if(!eqFloat(t.getMax(), this->_range[2]))
            throw std::invalid_argument("Tone mapping maximum value must be equal to range of V in HSV colors ");

        return Color({(*this)[0],(*this)[1],t.evaluate((*this)[2])},{this->_range[0], this->_range[1],1},HSV);
    }
}

bool Color::operator==(Color l) const
{
    for(unsigned int i=0;i<3;i++)
    {
        if (fabs((*this)[i] -l[i])>THRESHOLD_COLOR) return false; 
    }

    return this->_type == l._type;
}

std::ostream& operator<<(std::ostream& os,const Color& g)
{
    os << g[0] << " " << g[1] << " " << g[2];

    return os;
}
