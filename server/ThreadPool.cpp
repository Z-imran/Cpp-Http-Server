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
    threadpoolJoin();
}

void ThreadPool::enqueue(std::function<void ()> task) {
    {
        std::unique_lock<std::mutex> lock(mx);
        tasks.push(task);
    }
    cond.notify_one();
}

void ThreadPool::threadpoolJoin() {
    std::unique_lock<std::mutex> lock(mx);

    // Wait until both the task queue is empty and no thread is running a task
    cond.wait(lock, [this]() {
        return tasks.empty() && inUseThreads == 0;
    });

    // Signal shutdown
    running = false;
    cond.notify_all();  // Wake up any idle workers to let them exit

    lock.unlock();

    // Join all threads
    for (std::thread& t : threads) {
        if (t.joinable())
            t.join();
    }

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
            if (tasks.empty() && inUseThreads == 0) {
                cond.notify_all();
            }
        }
    }
}