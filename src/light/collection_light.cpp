#include "light/collection_light.hpp"

CollectionLight::CollectionLight(const VectorPunctualLight& lights, const VectorAreaLight& area_lights):
    _lights(lights), _area_lights(area_lights)
{
    if(lights.empty() && area_lights.empty())
    {
        throw std::invalid_argument("The collection of lights is empty");
    }

    double total_light = 0;

    for(const auto& one_light: lights)
    {
        total_light += one_light->luminance_max();
    }

    for(const auto& one_light: area_lights)
    {
        total_light += one_light->luminance_max();
    }

    for(const auto& one_light: lights)
    {
        this->_weights.push_back(one_light->luminance_max()/total_light);
    }

    for(const auto& one_light: area_lights)
    {
        this->_weights.push_back(one_light->luminance_max()/total_light);
    }
}

double CollectionLight::sample_light(std::shared_ptr<AbstractLight>& light) const
{
    double d = randomD(0,1);

    double sum_probabilities = 0;

    
    for(size_t i=0;i<this->_lights.size();i++)
    {
        if((sum_probabilities <= d) && (d <= (sum_probabilities + this->_weights[i])))
        {
            light = this->_lights[i];
            return this->_weights[i];
        }
        sum_probabilities += this->_weights[i];
    }

    for(size_t i=0;i<this->_area_lights.size();i++)
    {
        if((sum_probabilities <= d) && (d <= (sum_probabilities + this->_weights[i+this->_lights.size()])))
        {
            light = this->_area_lights[i];
            return this->_weights[i+this->_lights.size()];
        }
        sum_probabilities += this->_weights[i+this->_lights.size()];
    }

    throw std::runtime_error("Error sampling light");
}