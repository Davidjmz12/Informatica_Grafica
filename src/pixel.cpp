

#include "pixel.hpp"


Pixel::Pixel(float _red, float _green, float _blue, ColorEncode _type)
{
    this->colors[0] = _red;
    this->colors[1] = _green;
    this->colors[2] = _blue;
};

float Pixel::operator[](int index) const
{
    return this->colors[index];
}

float Pixel::max()
{
    float aux = this->colors[0];

    for(unsigned int i=1; i<3; ++i)
    {
        if(this->colors[i]>aux)
        {
            aux = this->colors[i];
        }
    }
    return aux;
}

float Pixel::min()
{
    float aux = this->colors[0];

    for(unsigned int i=1; i<3; ++i)
    {
        if(this->colors[i]<aux)
        {
            aux = this->colors[i];
        }
    }
    return aux;
}

Pixel Pixel::normalize() const
{
    return Pixel((*this)[0]/range,(*this)[1]/range,(*this)[2]/range,this->type);
}


Pixel Pixel::RGB_to_HSV() const
{

    if(this->type == HSV)
    {
        return (*this);
    }

    Pixel aux = this->normalize();

    float R = aux.colors[0];
    float G = aux.colors[1];
    float B = aux.colors[2];

    float max_col = aux.max();
    float min_col = aux.min();
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

    return Pixel(H,S,V,HSV);
}

Pixel Pixel::HSV_to_RGB() const
{

    if(this->type == RGB)
    {
        return (*this);
    }

    float H,S,V;
    H = this->colors[0];
    S = this->colors[1];
    V = this->colors[2];

    float alpha,beta,gamma;

    alpha = V*(1-S);

    beta = H==0?0:V*(1-(H-floor(H))*S);
    gamma = H==0?0:V*(1-(1-(H-floor(H)))*S);

    V *= range;
    alpha *= range;
    beta *= range;
    gamma *= range;
    if(H==0)
    {
        return Pixel(V,V,V,RGB);
    } else if(0<H<1)
    {
        return Pixel(V,gamma,alpha,RGB);
    } else if(1<=H<2)
    {
        return Pixel(beta,V,alpha,RGB);
    } else if(2<=H<3)
    {
        return Pixel(alpha,V,gamma,RGB);
    } else if(3<=H<4)
    {
        return Pixel(alpha,beta,V,RGB);
    } else if(4<=H<5)
    {
        return Pixel(gamma,alpha,V,RGB);
    } else
    {
        return Pixel(V,alpha,beta,RGB);
    }

}

bool Pixel::operator==(Pixel l) const
{
    for(unsigned int i=0;i<3;i++)
    {
        if (((*this)[i] -l[i])>threshold) return false; 
    }

    return true;
}

std::ostream& operator<<(std::ostream& os,const Pixel& g)
{
    std::string s = g.type == RGB ? "RGB":"HSV";

    os << s << "(" << g[0] << ", " << g[1] << ", " << g[2] << ")" << std::endl;

    return os;

}
