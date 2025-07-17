#include "ThreadPool.hpp"


// Constructor for ThreadPool using specified number of threads. 
ThreadPool::ThreadPool(size_t numThreads) {
    {
        std::unique_lock<std::mutex> lock(mx);
        running = true;
    }
    for (size_t i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(&ThreadPool::workerThread, this));
    }
}

// Destructor for ThreadPool. This joins all the threads and then sestroys the 
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mx);
        running = false;
    }
    cond.notify_all();
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void ThreadPool::enqueue(std::function<void ()> task) {
    {
        std::unique_lock<std::mutex> lock(mx);
        tasks.push(task);
    }
    cond.notify_one();
}

void ThreadPool::threadpoolJoin() {
    // Not Sure

}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void ()> task;
        {
            std::unique_lock<std::mutex> lock(mx);
            while (running && tasks.empty()) {
                cond.wait(lock);
            }

            if (!running && tasks.empty()) {
                return;
            }
            task = tasks.front();
            tasks.pop();
            inUseThreads++;
        }
        task();
        { 
            std::unique_lock<std::mutex> lock(mx);
            inUseThreads--;
        }
    }
}