

#include "color.hpp"


Color::Color(float c1, float c2, float c3, ColorEncoding type)
{
    if(type == RGB)
    {
        if(c1<0 || c1>RANGE_RGB || c2<0 || c2>RANGE_RGB || c3<0 || c3>RANGE_RGB)
        {
            throw std::invalid_argument("Color components of RGB must be between 0 and " + 
                                        std::to_string(RANGE_RGB));
        }
    } else if (type == HSV)
    {
        if(c1<0 || c1>RANGE_H)
        {
            throw std::invalid_argument("Color component (H) of HSV must be between 0 and " + 
                                        std::to_string(RANGE_H));
        } else if (c2<0 || c2>RANGE_SV || c3<0 || c3>RANGE_SV)
        {
            throw std::invalid_argument("Color components (SV) of HSV must be between 0 and " + 
                                        std::to_string(RANGE_SV));
        }
    } else 
    {
        throw std::invalid_argument("Invalid color encoding type");
    }
    
    this->_colors[0] = c1;
    this->_colors[1] = c2;
    this->_colors[2] = c3;
    this->_type = type;
};


Color::Color(float c1, float c2, float c3, float max_value_rgb)
{
    if(c1<0 || c1>max_value_rgb || c2<0 || c2>max_value_rgb || c3<0 || c3>max_value_rgb)
    {
        throw std::invalid_argument("Color components of RGB must be between 0 and" + 
                                    std::to_string(max_value_rgb));
    }
    this->_colors[0] = c1/max_value_rgb;
    this->_colors[1] = c1/max_value_rgb;
    this->_colors[2] = c1/max_value_rgb;
    this->_type = RGB;
}

Color::Color(float c1, float c2, float c3, float max_value_h, float max_value_sv)
{
    if(c1<0 || c1>max_value_h )
    {
        throw std::invalid_argument("Color component (H) of HSV must be between 0 and" + 
                                    std::to_string(max_value_h));
    } else if (c2<0 || c2>max_value_sv || c3<0 || c3>max_value_sv)
    {
        throw std::invalid_argument("Color components (SV) of HSV must be between 0 and" + 
                                    std::to_string(max_value_sv));
    }
    this->_colors[0] = c1/max_value_h*6;
    this->_colors[1] = c1/max_value_sv;
    this->_colors[2] = c1/max_value_sv;
    this->_type = HSV;
}

float Color::operator[](int index) const
{
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

    float R = this->_colors[0];
    float G = this->_colors[1];
    float B = this->_colors[2];

    float max_col = this->max();
    float min_col = this->min();
    float dif = max_col-min_col;

    float H,S,V;

    if(dif == 0)
    {
        H = 0;
    } else if (max_col == R)
    {
        H = ((G-B)/dif,6);
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

    return Color(H,S,V,HSV);
}

Color Color::HSV_to_RGB() const
{

    if(this->_type == RGB)
    {
        return (*this);
    }

    float H,S,V;
    H = this->_colors[0];
    S = this->_colors[1];
    V = this->_colors[2];

    float alpha,beta,gamma;

    alpha = V*(1-S);

    beta = H==0?0:V*(1-(H-floor(H))*S);
    gamma = H==0?0:V*(1-(1-(H-floor(H)))*S);

    V *= RANGE_RGB;
    alpha *= RANGE_RGB;
    beta *= RANGE_RGB;
    gamma *= RANGE_RGB;
    if(H==0)
    {
        return Color(V,V,V,RGB);
    } else if(0<H && H<1)
    {
        return Color(V,gamma,alpha,RGB);
    } else if(1<=H && H<2)
    {
        return Color(beta,V,alpha,RGB);
    } else if(2<=H && H<3)
    {
        return Color(alpha,V,gamma,RGB);
    } else if(3<=H && H<4)
    {
        return Color(alpha,beta,V,RGB);
    } else if(4<=H && H<5)
    {
        return Color(gamma,alpha,V,RGB);
    } else
    {
        return Color(V,alpha,beta,RGB);
    }

}

ColorEncoding Color::get_type() const
{
    return this->_type;
}

Color Color::apply_tone_mapping(ToneMapping t) const
{
    if(this->_type == RGB)
    {
        throw std::invalid_argument("Tone mapping can only be applied to HSV colors");
    } else if (t.getMax() != 6)
    {
        throw std::invalid_argument("Tone mapping can only be applied to HSV colors with a maximum of 6");
    } else 
    {
        return Color(t.evaluate((*this)[0]),(*this)[1],(*this)[2],HSV);
    }
}


bool Color::operator==(Color l) const
{
    for(unsigned int i=0;i<3;i++)
    {
        if (((*this)[i] -l[i])>THRESHOLD_COLOR) return false; 
    }

    return this->_type == l._type;
}

std::ostream& operator<<(std::ostream& os,const Color& g)
{
    os << g[0] << " " << g[1] << " " << g[2];

    return os;
}
