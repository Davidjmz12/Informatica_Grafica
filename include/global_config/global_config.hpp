#pragma once


#include <string>
#include <unordered_map>
#include <any>

using HashMap = std::unordered_map<std::string, std::any>;

/**
 * The GlobalConf class defines the `get_instance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class GlobalConf
{

    /**
     * The GlobalConf's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

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

    size_t get_number_of_rays(){
        return std::any_cast<int>(this->get("rays"));
    }


    auto get(const std::string key)
        -> std::any
    {
        try {
            return _values.at(key);
        } catch (const std::out_of_range& e) {
            throw std::invalid_argument("Key not found");
        }
    }

};
