#include "color/spectral_color.hpp"


SpectralColor::SpectralColor():
    _chanels({})
{}


SpectralColor::SpectralColor(std::array<double,32> chanels_32):
    _chanels(chanels_32)
{}

SpectralColor::SpectralColor(std::array<double,16> chanels_16):
    _chanels({})
{
    for(size_t i=0; i<16; ++i)
    {
        this->_chanels[2*i] = chanels_16[i];
    }
}

SpectralColor::SpectralColor(std::array<double,8> chanels_8):
    _chanels({})
{
    for(size_t i=0; i<8; ++i)
    {
        this->_chanels[4*i] = chanels_8[i];
    }
}

SpectralColor::SpectralColor(std::array<double,3> rgb):
    _chanels({})
{
    for(size_t i=16; i<32; ++i)
    {
        this->_chanels[i] = rgb[0];
    }

    for(size_t i=8; i<16; ++i)
    {
        this->_chanels[i] = rgb[1];
    }

    for(size_t i=0; i<8; ++i)
    {
        this->_chanels[i] = rgb[2];
    }

}

SpectralColor::SpectralColor(std::function<double(double)> f):
    _chanels({})
{
    for(size_t i=0; i<SIZE; ++i)
    {
        this->_chanels[i] = f(WAVELENGTHS[i]);
    }
}

SpectralColor::SpectralColor(double intensity)
{
    for(size_t i=0; i<SIZE; ++i)
    {
        this->_chanels[i] = intensity;
    }
}

ColorRGB SpectralColor::to_rgb() const
{
    double X = 0, Y = 0, Z = 0;

    // Integration by mean of the color channels
    for(size_t i=0; i<SIZE; ++i)
    {
        std::array<double,3> cie = CIE_1931_curves(WAVELENGTHS[i]);
        X += this->_chanels[i]*cie[0]*increment;
        Y += this->_chanels[i]*cie[1]*increment;
        Z += this->_chanels[i]*cie[2]*increment;
    }

    double R = 3.2404542*X - 1.5371385*Y - 0.4985314*Z;
    double G = -0.9692660*X + 1.8760108*Y + 0.0415560*Z;
    double B = 0.0556434*X - 0.2040259*Y + 1.0572252*Z;

    //double R = X;
    //double G = Y;
    //double B = Z;

    R = gamma_correction(R);
    G = gamma_correction(G);
    B = gamma_correction(B);

    R = std::max(0.0,R);
    G = std::max(0.0,G);
    B = std::max(0.0,B);

    return ColorRGB({R,G,B});
}

SpectralColor SpectralColor::apply_tone_mapping(ToneMapping* t) const
{
    std::array<double,SIZE> new_chanels;
    for(size_t i=0; i<SIZE; ++i)
    {
        new_chanels[i] = t->evaluate(this->_chanels[i]);
    }
    return SpectralColor(new_chanels);
}

std::string SpectralColor::to_string() const
{
    std::string s = "SpectralColor(";
    for(size_t i=0; i<SIZE; ++i)
    {
        s += std::to_string(this->_chanels[i]) + " ";
    }
    return s + ")";
}

double SpectralColor::operator[](int index) const
{
    if(index<0 || index>=SIZE)
        throw std::out_of_range("Invalid index for color component");

    return this->_chanels[index];
}

SpectralColor SpectralColor::operator+(SpectralColor c) const
{
    std::array<double,SIZE> new_chanels;
    for(size_t i=0; i<SIZE; ++i)
        new_chanels[i] = this->_chanels[i] + c[i];
    return SpectralColor(new_chanels);
}

SpectralColor SpectralColor::operator*(SpectralColor c) const
{

    std::array<double,SIZE> new_chanels;
    for(size_t i=0; i<SIZE; ++i)
        new_chanels[i] = this->_chanels[i] * c[i];
    return SpectralColor(new_chanels);
}

SpectralColor SpectralColor::operator*(double f) const
{
    std::array<double,SIZE> new_chanels;
    for(size_t i=0; i<SIZE; ++i)
        new_chanels[i] = this->_chanels[i] * f;
    return SpectralColor(new_chanels);
}
SpectralColor SpectralColor::operator/(double f) const
{
    std::array<double,SIZE> new_chanels;
    for(size_t i=0; i<SIZE; ++i)
        new_chanels[i] = this->_chanels[i] / f;
    return SpectralColor(new_chanels);
}

std::ostream& operator<<(std::ostream& os, const SpectralColor& g)
{
    os << g.to_string();

    return os;
}

bool SpectralColor::operator==(SpectralColor c) const
{
    for(size_t i=0;i<SIZE;i++)
    {
        if (!eqD((*this)[i],c[i])) return false; 
    }

    return true;
}

bool SpectralColor::check_less_1() const
{
    for(size_t i=0;i<SIZE;i++)
    {
        if (gtD((*this)[i],1.0)) return false; 
    }

    return true;
}