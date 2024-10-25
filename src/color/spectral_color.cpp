#include "color/spectral_color.hpp"

SpectralColor::SpectralColor():
    _chanels({0,0}), _size(1)
{}
    
SpectralColor::SpectralColor(std::vector<double> chanels):
    _chanels(chanels), _size(chanels.size())
{
    for(double chan: chanels)
    {
        if(chan<0)
            throw std::invalid_argument("The color channels must be higher than 0.");
    }

    if(this->_size <= 0)
        throw std::invalid_argument("The number of channels must be higher than 0.");

    this->_wave_lengths = std::vector<double>(this->_size);
    for(size_t i=0; i<this->_size; ++i)
    {
        this->_wave_lengths[i] = (380 + (i+1)*(780-380)/(this->_size+1));
    }
}

SpectralColor::SpectralColor(std::vector<double> chanels, std::vector<double> wave_lengths):
    _chanels(chanels), _wave_lengths(wave_lengths), _size(chanels.size())
{
    for(size_t i=0; i<this->_size; ++i)
    {
        if(i<this->_size-1 && this->_wave_lengths[i] >= this->_wave_lengths[i+1])
            throw std::invalid_argument("The wave lengths must be in strict increasing order.");

        if(wave_lengths[i]<380 || wave_lengths[i]>780)
            throw std::invalid_argument("The wave lengths must be between 380 and 780.");

        if(chanels[i]<0)
            throw std::invalid_argument("The color channels must be higher than 0.");
    }

    if(this->_size <= 0)
        throw std::invalid_argument("The number of channels must be higher than 0.");

    if(this->_size != this->_wave_lengths.size())
        throw std::invalid_argument("The number of channels must be equal to the size of the wave lengths.");
}

SpectralColor SpectralColor::from_rgb(std::array<double,3> rgb)
{
    std::vector<double> wave_lengths = {435, 546, 700};
    std::vector<double> chanels = {rgb[2], rgb[2], rgb[1]};

    return SpectralColor(chanels, wave_lengths);
}

std::vector<double> SpectralColor::get_wave_lengths() const
{
    return this->_wave_lengths;
}

double SpectralColor::get_increment(size_t i) const
{
    if(i==0)
        return this->_wave_lengths[1]-380;
    if(i==this->_size-1)
        return 780-this->_wave_lengths[this->_size-2];

    return (this->_wave_lengths[i+1]-this->_wave_lengths[i-1]);
}

ColorRGB SpectralColor::to_rgb() const
{
    double X = 0, Y = 0, Z = 0;

    // Integration by mean of the color channels
    for(size_t i=0; i<this->_size; ++i)
    {
        double increment = get_increment(i);
        std::array<double,3> cie = CIE_1931_curves(this->_wave_lengths[i]);
        X += this->_chanels[i]*cie[0]*increment;
        Y += this->_chanels[i]*cie[1]*increment;
        Z += this->_chanels[i]*cie[2]*increment;
    }

    X /= this->_size;
    Y /= this->_size;
    Z /= this->_size;

    double R = 3.2406*X - 1.5372*Y - 0.4986*Z;
    double G = -0.9689*X + 1.8758*Y + 0.0415*Z;
    double B = 0.0557*X - 0.2040*Y + 1.0570*Z;

    //R = gamma_correction(R);
    //G = gamma_correction(G);
    //B = gamma_correction(B);

    return ColorRGB({R,G,B});
}

SpectralColor SpectralColor::apply_tone_mapping(ToneMapping* t) const
{
    std::vector<double> new_chanels;
    for(size_t i=0; i<this->_size; ++i)
    {
        new_chanels.push_back(t->evaluate(this->_chanels[i]));
    }
    return SpectralColor(new_chanels);
}

std::string SpectralColor::to_string() const
{
    std::string s = "SpectralColor(";
    for(size_t i=0; i<this->_size; ++i)
    {
        s += std::to_string(this->_chanels[i]) + " ";
    }
    return s + ")";
}

double SpectralColor::operator[](int index) const
{
    if(index<0 || index>=this->_size)
        throw std::out_of_range("Invalid index for color component");

    return this->_chanels[index];
}

SpectralColor SpectralColor::operator+(SpectralColor c) const
{
    if(this->_size != c._size)
        throw std::invalid_argument("The number of channels must be equal to the size of the color.");

    std::vector<double> new_chanels;
    for(size_t i=0; i<this->_size; ++i)
        new_chanels.push_back(this->_chanels[i] + c[i]);
    return SpectralColor(new_chanels);
}

SpectralColor SpectralColor::operator*(SpectralColor c) const
{
    if(this->_size != c._size)
        throw std::invalid_argument("The number of channels must be equal to the size of the color.");

    std::vector<double> new_chanels;
    for(size_t i=0; i<this->_size; ++i)
        new_chanels.push_back(this->_chanels[i] * c[i]);
    return SpectralColor(new_chanels);
}

SpectralColor SpectralColor::operator*(double f) const
{
    std::vector<double> new_chanels;
    for(size_t i=0; i<this->_size; ++i)
        new_chanels.push_back(this->_chanels[i] * f);
    return SpectralColor(new_chanels);
}
SpectralColor SpectralColor::operator/(double f) const
{

    std::vector<double> new_chanels;
    for(size_t i=0; i<this->_size; ++i)
        new_chanels.push_back(this->_chanels[i] / f);
    return SpectralColor(new_chanels);
}

std::ostream& operator<<(std::ostream& os, const SpectralColor& g)
{
    os << g.to_string();

    return os;
}

bool SpectralColor::operator==(SpectralColor c) const
{
    if(this->_size != c._size)
        return false;

    for(size_t i=0;i<this->_size;i++)
    {
        if (!eqD((*this)[i],c[i]) || !eqD(this->get_wave_lengths()[i], c.get_wave_lengths()[i])) return false; 
    }

    return true;
}
