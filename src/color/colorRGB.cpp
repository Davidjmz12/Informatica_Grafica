#include "color/colorRGB.hpp"


ColorRGB::ColorRGB():
    _colors({0,0,0})
{}

ColorRGB::ColorRGB(const SC3& rgb):
    _colors(rgb)
{
    if(rgb[0]<0 || rgb[1]<0 || rgb[2]<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}

ColorRGB::ColorRGB(const SC32& channels_32):
    _colors({channels_32[25], channels_32[13], channels_32[4]})
{
    if(channels_32[25]<0 || channels_32[13]<0 || channels_32[4]<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}

ColorRGB::ColorRGB(const SC16& channels_16):
    _colors({channels_16[12], channels_16[6], channels_16[2]})
{
    if(channels_16[12]<0 || channels_16[6]<0 || channels_16[2]<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}

ColorRGB::ColorRGB(const SC8& channels_8):
    _colors({channels_8[6], channels_8[3], channels_8[1]})
{
    if(channels_8[6]<0 || channels_8[3]<0 || channels_8[1]<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}

ColorRGB::ColorRGB(const std::function<double(double)>& f):
    _colors({f(700), f(550), f(435)})
{
    if(f(700)<0 || f(550)<0 || f(435)<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}

ColorRGB::ColorRGB(const double intensity):
    _colors({intensity, intensity, intensity})
{
    if(intensity<0)
        throw std::invalid_argument("Color intensity must be higher than 0.");
}

ColorRGB ColorRGB::to_rgb() const
{
    return *this;
}


ColorRGB ColorRGB::apply_tone_mapping(const std::unique_ptr<ToneMapping>& t, const size_t new_resolution) const
{
    std::array<double, 3> new_colors{};
    for(size_t i=0; i<3; ++i)
    {
        new_colors[i] = t->evaluate(this->_colors[i])*static_cast<double>(new_resolution);
    }
    return ColorRGB(new_colors);
}


std::string ColorRGB::to_string() const
{
    std::string s =
        std::to_string(static_cast<int>(this->_colors[0])) + " " +
        std::to_string(static_cast<int>(this->_colors[1])) + " " +
        std::to_string(static_cast<int>(this->_colors[2]));
    return s;
}

double ColorRGB::luminance_mean() const
{
    return (this->_colors[0] + this->_colors[1] + this->_colors[2]) / 3;
}

double ColorRGB::luminance_max() const
{
    return std::max(this->_colors[0], std::max(this->_colors[1], this->_colors[2]));
}


/* Operators */

/**
 * @brief Access color components by index.
 * @param index Index of the color component.
 * @return Value of the color component at the given index.
 * @throws std::out_of_range if the index is out of bounds.
 */
double ColorRGB::operator[](const size_t index) const
{
    if(index>2)
        throw std::out_of_range("Invalid index for color component");

    return this->_colors[index];
}


/**
 * @brief Output the color to an output stream.
 * @param os Output stream.
 * @param g Color to output.
 * @return Output stream.
 */
std::ostream& operator<<(std::ostream& os, const ColorRGB& g)
{
    os << g.to_string();
    return os;
}


ColorRGB ColorRGB::operator*(const ColorRGB& c) const
{
    std::array<double, 3> new_colors{};
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] * c[i];
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator+(const ColorRGB& c) const
{
    std::array<double, 3> new_colors{};
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] + c[i];
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator*(const double f) const
{
    std::array<double, 3> new_colors{};
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] * f;
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator/(const double f) const
{
    std::array<double, 3> new_colors{};
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] / f;
    return ColorRGB(new_colors);
}

/**
 * @brief Compare two colors for equality.
 * @param l Color to compare with.
 * @return True if colors are equal, false otherwise.
 */
bool ColorRGB::operator==(const ColorRGB& l) const
{
    for(size_t i=0;i<3;i++)
    {
        if (!eqD((*this)[i],l[i])) return false; 
    }

    return true;
}


bool ColorRGB::operator<=(const double f) const
{
    for(size_t i=0;i<3;i++)
    {
        if (!leD((*this)[i],f)) return false; 
    }

    return true;
}


