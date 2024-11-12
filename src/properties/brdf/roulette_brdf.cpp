#include "properties/brdf/roulette_brdf.hpp"


RouletteBRDF::RouletteBRDF(std::vector<std::shared_ptr<BRDF>> brdfs, std::vector<double> weights)
    : _brdfs(brdfs), _weights(weights), _sampled_ray_index(-1)
{
    SpectralColor sum_colors;
    for(size_t i=0; i<brdfs.size(); ++i)
    {
        sum_colors = sum_colors + brdfs[i]->get_color();
    }
    if(!(sum_colors <= 1))
        throw std::invalid_argument("The sum of the colors of the BRDFs must be less or equal to 1");

    if(brdfs.size() != weights.size())
        throw std::invalid_argument("The number of BRDFs must be equal to the number of weights");

    double sum_weights = 0;
    for(size_t i=0; i<weights.size(); ++i)
    {
        sum_weights += weights[i];
    }

    if(!eqD(sum_weights,1))
        throw std::invalid_argument("The sum of the weights must be equal to 1");
    
}

SpectralColor RouletteBRDF::eval(Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry) const
{
    if(_sampled_ray_index == -1)
        throw std::invalid_argument("No ray has been sampled yet");

    return _brdfs[_sampled_ray_index]->eval(w_i, w_0, x, n, ref_coef_entry)*this->_weights[_sampled_ray_index];
}

bool RouletteBRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering)
{
    double r = randomD(0,1);
    double sum = 0;
    for(size_t i=0; i<_weights.size(); ++i)
    {
        if(sum <= r && r < sum + _weights[i])
        {
            _sampled_ray_index = i;
            return _brdfs[i]->sample_ray(w_0, x, n, ref_coef_entry, sampled_ray, is_entering);
        }
        sum += _weights[i];	
    }
    return false;
}

std::string RouletteBRDF::to_string() const
{
    std::string s = "RouletteBRDF: ";
    for(size_t i=0; i<_brdfs.size(); ++i)
    {
        s += _brdfs[i]->to_string() + " " + std::to_string(_weights[i]) + "\n";
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, const RouletteBRDF& b)
{
    os << b.to_string();
    return os;
}