#pragma once


#include <string>
#include <unordered_map>
#include <any>

#include "metrics/metrics.hpp"

using HashMap = std::unordered_map<std::string, std::any>;

enum class RenderType
{
    RAY_TRACING,
    PHOTON_MAPPING
};

/**
 * The GlobalConf class defines the `get_instance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class GlobalConf
{


protected:
    GlobalConf(const HashMap values): 
        _values(values)
    {}

    static GlobalConf* _conf;

    HashMap _values;

public:

    GlobalConf(GlobalConf &other) = delete;
    void operator=(const GlobalConf &) = delete;

    static GlobalConf *get_instance(const HashMap conf)
    {
        if(_conf==nullptr){
            GlobalConf::_conf = new GlobalConf(conf);
        }
        return _conf; 
    }

    static GlobalConf *get_instance()
    {
        return GlobalConf::get_instance({});
    }

    size_t get_number_of_threads(){
        return std::any_cast<int>(this->get("threads"));
    }

    RenderType get_render_type(){
        return std::any_cast<RenderType>(this->get("render-type"));
    }

    size_t get_task_size(){
        return std::any_cast<int>(this->get("task-size"));
    }

    size_t get_number_of_rays(){
        return std::any_cast<int>(this->get("rays"));
    }

    size_t get_number_of_bounces(){
        return std::any_cast<int>(this->get("bounces"));
    }

    size_t get_max_depth(){
        return std::any_cast<int>(this->get("max-depth"));
    }

    size_t get_number_of_photons(){
        return std::any_cast<int>(this->get("num-photons"));
    }

    double get_radius(){
        return std::any_cast<double>(this->get("radius"));
    }

    size_t get_max_photon_num(){
        return std::any_cast<int>(this->get("max-photon-num"));
    }


    auto get(const std::string key)
        -> std::any
    {
        try {
            return _values.at(key);
        } catch (const std::out_of_range& e) {
            throw std::invalid_argument("Key " + key + " not found");
        }
    }

    bool has(const std::string key)
    {
        return _values.find(key) != _values.end();
    }

    bool has_metrics()
    {
        return this->has("is-metrics") && std::any_cast<bool>(this->get("is-metrics"));
    }

    Metrics& get_metrics()
    {
        if(!this->has_metrics())
            throw std::runtime_error("No metrics available");

        return std::any_cast<Metrics&>(_values.at("metrics"));
    }

    void print()
    {
        std::cout << "Global configuration:" << std::endl;
        for (const auto& [key, value] : _values)
        {
            std::cout << key << ": " << value << std::endl;
        }
    }

};
