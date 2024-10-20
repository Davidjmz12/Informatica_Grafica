#pragma once

#include <chrono>
#include <unordered_map>
#include <iostream>
#include <fstream>

using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using Duration = std::chrono::duration<double>;

enum class State {
    RUNNING,
    FINISHED
};

struct Counter {
    size_t count;
    std::string description;
};

struct TimerMetric {
    Time start;
    Time end;
    State state;
    std::string description;
};

struct TimeMetric {
    size_t count;
    Time start;
    Duration duration;
    std::string description;
};

using TimerHash = std::unordered_map<std::string, TimerMetric>;
using TimeHash = std::unordered_map<std::string, TimeMetric>;
using CounterHash = std::unordered_map<std::string, Counter>;


class Metrics {
private:
    TimerHash _timers;
    TimeHash _times;
    CounterHash _counters;

public:
    Metrics() = default;

    bool is_timer(std::string name)
    {
        return _timers.find(name) != _timers.end();
    }

    bool is_time(std::string name)
    {
        return _times.find(name) != _times.end();
    }

    bool is_counter(std::string name)
    {
        return _counters.find(name) != _counters.end();
    }

    void add_counter(std::string name, std::string description = "")
    {
        if(this->is_counter(name))
            throw std::runtime_error("Counter already exists");

        _counters[name] = Counter{
            0,
            description
        };
    }

    void increment_counter(std::string name)
    {
        if(!this->is_counter(name))
            throw std::runtime_error("Counter does not exist");

        _counters[name].count++;
    }

    void init_time_metric(std::string name, std::string description = "")
    {
        if(this->is_time(name))
            throw std::runtime_error("Timer already exists");
        
        _times[name] = TimeMetric{
            0,
            std::chrono::high_resolution_clock::now(),
            Duration{0},
            description = description
        };
        
    }

    void start_duration_time_metric(std::string name)
    {
        if(!this->is_time(name))
            throw std::runtime_error("Time does not exist");

        _times[name].start = std::chrono::high_resolution_clock::now();
 
    }

    void add_duration_to_time_metric(std::string name)
    {
        if(!this->is_time(name))
            throw std::runtime_error("Time does not exist"); 

        Time t = std::chrono::high_resolution_clock::now();
        _times[name].duration += t - _times[name].start;
        _times[name].start = t;
        _times[name].count++;
    }

    void start_timer_metric(std::string name, std::string description = "")
    {
        if(this->is_timer(name))
            throw std::runtime_error("Timer already exists");
        
        _timers[name] = TimerMetric{
            std::chrono::high_resolution_clock::now(),
            std::chrono::high_resolution_clock::now(),
            State::RUNNING,
            description = description
        };
    }
    
    void finish_timer_metric(std::string name)
    {
        if(!this->is_timer(name))
            throw std::runtime_error("Timer does not exist");

        if(_timers[name].state == State::FINISHED)
            throw std::runtime_error("Timer already finished");

        _timers[name].end = std::chrono::high_resolution_clock::now();
        _timers[name].state = State::FINISHED;
    } 




    void print_metrics(std::ostream& f = std::cout)
    {
        f << "Metrics:" << std::endl << std::endl;
        f << "Timers:" << std::endl;
        for(auto& [name, timer] : _timers)
        {
            if(timer.state == State::FINISHED)
            {
                std::chrono::duration<double> elapsed_seconds = timer.end - timer.start;
                f << "Timer: " << name << "\n\tDescription: " << timer.description << "\n\tTime: " << elapsed_seconds.count() << "s" << std::endl;
            }
        }

        f << "Times:" << std::endl;
        for(auto& [name, time] : _times)
        {
            f << "Time: " << name << "\n\tDescription: " << time.description << "\n\tTask accepted: " << time.count << "\n\tTime: " << time.duration.count() << "s" << std::endl;
        }

        f << "Counters:" << std::endl;
        for(auto& [name, counter] : _counters)
        {
            f << "Counter: " << name << "\n\tDescription: " << counter.description << "\n\tCount: " << counter.count << std::endl;
        }
    }

    void clear_metrics()
    {
        _timers.clear();
        _times.clear();
    }

    void write_metrics(std::string filename)
    {
        std::ofstream file;
        file.open(filename);
        print_metrics(file);
    }

};