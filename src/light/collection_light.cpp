#include "light/collection_lights.hpp"

CollectionLight::CollectionLight(const LightVector& lights):
    _lights(lights)
{
    double total_light = 0;

    for(const auto& one_light: lights)
    {
        total_light += one_light->luminance_max();
    }

    for(const auto& one_light: lights)
    {
        this->_weights.push_back(one_light->luminance_max()/total_light);
    }

}

double CollectionLight::sample_light(PunctualLight& light)
{
    double d = randomD(0,1);

    double sum_probabilities = 0;

    
    for(size_t i=0;i<this->_lights.size();i++)
    {
        if(sum_probabilities <= d <= (sum_probabilities + this->_weights[i]))
        {
            light = *this->_lights[i].get();
            return this->_weights[i];
        }
        sum_probabilities += this->_weights[i];
    }
}