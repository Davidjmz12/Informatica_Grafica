#include "color/colorRGB.hpp"

ColorRGB::ColorRGB(std::array<double, 3> colors):
    _colors(colors)
{
    if(colors[0]<0 || colors[1]<0 || colors[2]<0)
        throw std::invalid_argument("Color components must be higher than 0.");
}


ColorRGB::ColorRGB():
    _colors({0,0,0})
{}

ColorRGB ColorRGB::apply_tone_mapping(ToneMapping* t, size_t new_resolution) const
{
    std::array<double, 3> new_colors;
    for(size_t i=0; i<3; ++i)
    {
        new_colors[i] = t->evaluate(this->_colors[i])*new_resolution;
    }
    return ColorRGB(new_colors);
}


std::string ColorRGB::to_string() const
{
    std::string s = std::to_string((int)this->_colors[0]) + " " + std::to_string((int)this->_colors[1]) + " " + std::to_string((int)this->_colors[2]);
    return s;
}


/* Operators */

/**
 * @brief Access color components by index.
 * @param index Index of the color component.
 * @return Value of the color component at the given index.
 * @throws std::out_of_range if the index is out of bounds.
 */
double ColorRGB::operator[](int index) const
{
    if(index<0 || index>2)
        throw std::out_of_range("Invalid index for color component");

    return this->_colors[index];
}


/**
 * @brief Compare two colors for equality.
 * @param l Color to compare with.
 * @return True if colors are equal, false otherwise.
 */
bool ColorRGB::operator==(ColorRGB l) const
{
    for(size_t i=0;i<3;i++)
    {
        if (!eqD((*this)[i],l[i])) return false; 
    }

    return true;
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


ColorRGB ColorRGB::operator*(ColorRGB c) const
{
    std::array<double, 3> new_colors;
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] * c[i];
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator+(ColorRGB c) const
{
    std::array<double, 3> new_colors;
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] + c[i];
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator*(double f) const
{
    std::array<double, 3> new_colors;
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] * f;
    return ColorRGB(new_colors);
}

ColorRGB ColorRGB::operator/(double f) const
{
    std::array<double, 3> new_colors;
    for(size_t i=0; i<3; ++i)
        new_colors[i] = this->_colors[i] / f;
    return ColorRGB(new_colors);
}
