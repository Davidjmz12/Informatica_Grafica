#include "color/color.hpp"

#ifdef SPECTRAL_COLOR
Color::Color():
    _channels({})
{}

Color::Color(const std::array<double,32>& channels_32):
    _channels(channels_32)
{}

Color::Color(const std::array<double,16>& channels_16):
    _channels({})
{
    for(size_t i=0; i<16; ++i)
    {
        this->_channels[2*i] = channels_16[i];
    }
}

Color::Color(const std::array<double,8>& channels_8):
    _channels({})
{
    for(size_t i=0; i<8; ++i)
    {
        this->_channels[4*i] = channels_8[i];
    }
}

Color::Color(const std::array<double,3>& rgb):
    _channels({})
{
    for(size_t i=16; i<32; ++i)
    {
        this->_channels[i] = rgb[0];
    }

    for(size_t i=8; i<16; ++i)
    {
        this->_channels[i] = rgb[1];
    }

    for(size_t i=0; i<8; ++i)
    {
        this->_channels[i] = rgb[2];
    }

}

Color::Color(const std::function<double(double)>& f):
    _channels({})
{
    for(size_t i=0; i<SIZE; ++i)
    {
        this->_channels[i] = f(WAVELENGTHS[i]);
    }
}

Color::Color(const double intensity)
{
    for(size_t i=0; i<SIZE; ++i)
    {
        this->_channels[i] = intensity;
    }
}

double Color::luminance_mean() const
{
    double sum = 0;
    for(size_t i=0; i<SIZE; i++)
    {
        sum += this->_channels[i];
    }

    return sum/static_cast<double>(SIZE);
}

double Color::luminance_max() const
{
    double max = 0;
    for(size_t i=0; i<SIZE; i++)
    {
        max = max<this->_channels[i]?this->_channels[i]:max;
    }
    return max;
}

ColorRGB Color::to_rgb() const
{
    double X = 0, Y = 0, Z = 0;

    // Integration by mean of the color channels
    for(size_t i=0; i<SIZE; ++i)
    {
        std::array<double,3> cie = CIE_1931_curves(WAVELENGTHS[i]);
        X += this->_channels[i]*cie[0]*increment;
        Y += this->_channels[i]*cie[1]*increment;
        Z += this->_channels[i]*cie[2]*increment;
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

    return ColorRGB(SC3{R,G,B});
}

Color Color::apply_tone_mapping(const std::unique_ptr<ToneMapping>& t) const
{
    std::array<double,SIZE> new_channels{};
    for(size_t i=0; i<SIZE; ++i)
    {
        new_channels[i] = t->evaluate(this->_channels[i]);
    }
    return Color(new_channels);
}

std::string Color::to_string() const
{
    std::string s = "Color(";
    for(size_t i=0; i<SIZE; ++i)
    {
        s += std::to_string(this->_channels[i]) + " ";
    }
    return s + ")";
}

double Color::operator[](const size_t index) const
{
    if(index>=SIZE)
        throw std::out_of_range("Invalid index for color component");

    return this->_channels[index];
}

Color Color::operator+(const Color& c) const
{
    std::array<double,SIZE> new_channels{};
    for(size_t i=0; i<SIZE; ++i)
        new_channels[i] = this->_channels[i] + c[i];
    return Color(new_channels);
}

Color Color::operator*(const Color& c) const
{

    std::array<double,SIZE> new_channels{};
    for(size_t i=0; i<SIZE; ++i)
        new_channels[i] = this->_channels[i] * c[i];
    return Color(new_channels);
}

Color Color::operator*(const double f) const
{
    std::array<double,SIZE> new_channels{};
    for(size_t i=0; i<SIZE; ++i)
        new_channels[i] = this->_channels[i] * f;
    return Color(new_channels);
}
Color Color::operator/(const double f) const
{
    std::array<double,SIZE> new_channels{};
    for(size_t i=0; i<SIZE; ++i)
        new_channels[i] = this->_channels[i] / f;
    return Color(new_channels);
}

std::ostream& operator<<(std::ostream& os, const Color& g)
{
    os << g.to_string();

    return os;
}

bool Color::operator==(const Color& c) const
{
    for(size_t i=0;i<SIZE;i++)
    {
        if (!eqD((*this)[i],c[i])) return false; 
    }

    return true;
}

bool Color::operator<=(const double f) const
{
    for(size_t i=0;i<SIZE;i++)
    {
        if (!leD((*this)[i],f)) return false; 
    }

    return true;
}

#endif
