#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

#include "metrics/metrics.hpp"
#include "global_config/global_config.hpp"

class ThreadPool {

private:
    // Workers (threads) in the pool
    std::vector<std::thread> _workers;

    // Task queue
    std::queue<std::function<void()>> _tasks;

    // Synchronization
    std::mutex _queueMutex;
    std::condition_variable _condition;

    // Flag to stop all threads
    std::atomic<bool> _stopFlag;

public:

    void thread_work(size_t id)
    {
        GlobalConf *gc = GlobalConf::get_instance();
        bool has_metrics = gc->has_metrics();

        std::string name_working = "thread_" + std::to_string(id) + "_working";
        std::string name_waiting = "thread_" + std::to_string(id) + "_waiting";

        {
            // Critical section for queue access
            std::unique_lock<std::mutex> lock(this->_queueMutex);
            if (has_metrics)
            {
                Metrics& m = gc->get_metrics();
                m.init_time_metric(name_working, "Thread " + std::to_string(id) + " working time");
                m.init_time_metric(name_waiting, "Thread " + std::to_string(id) + " waiting time");
            }
        }


        while (true) {
            std::function<void()> task;

            {   
                // Critical section for queue access
                std::unique_lock<std::mutex> lock(this->_queueMutex);

                if (has_metrics)
                {
                    Metrics& m = gc->get_metrics();
                    m.start_duration_time_metric(name_waiting);
                }
                

                // Wait until we are signaled for a task or to stop
                this->_condition.wait(lock, [this]() {
                    return this->_stopFlag || !this->_tasks.empty();
                });

                if (has_metrics)
                {
                    Metrics& m = gc->get_metrics();
                    m.add_duration_to_time_metric(name_waiting);
                }

                if (this->_stopFlag && this->_tasks.empty()) {
                    return; // Break out of the loop and end the thread
                }

                task = std::move(this->_tasks.front());
                this->_tasks.pop();
            }

            if (has_metrics)
            {
                Metrics& m = gc->get_metrics();
                m.start_duration_time_metric(name_working);
            }

            // Execute the task
            task();

            if (has_metrics)
            {
                Metrics& m = gc->get_metrics();
                m.add_duration_to_time_metric(name_working);
            }

        }
    }


    // Constructor: Creates the thread pool and starts the worker threads
    ThreadPool(size_t numThreads) : _stopFlag(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            _workers.emplace_back(
                [this,i] {
                    this->thread_work(i);
                }
            );
        }
    }

    // Destructor: Joins all threads and shuts down the pool
    ~ThreadPool() {
        {   // Critical section to set stop flag
            std::unique_lock<std::mutex> lock(_queueMutex);
            _stopFlag = true;
        }
        
        _condition.notify_all(); // Wake up all threads to finish
        for (std::thread &worker : _workers) {
            worker.join(); // Wait for all threads to finish
        }
    }

    // Submit a task to the thread pool
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
            
        using returnType = typename std::result_of<F(Args...)>::type;

        // Create a packaged task for the function
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<returnType> result = task->get_future();

        {   // Critical section for queue access
            std::unique_lock<std::mutex> lock(_queueMutex);

            // Don't allow enqueueing after stopping the pool
            if (_stopFlag) {
                throw std::runtime_error("Cannot enqueue on stopped ThreadPool");
            }

            // Add the task to the queue
            _tasks.emplace([task]() { (*task)(); });
        }

        _condition.notify_one(); // Notify a thread that there is a new task
        return result;
    }
};
