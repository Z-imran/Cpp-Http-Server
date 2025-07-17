#include <cstddef>
#include <functional>
#include <thread>
#include <queue>
#ifndef THREADPOOL_UNIQUE
#define THREADPOOL_UNIQUE

/**
 * Class template for the threadpool which allows us to asynchrounously handle multiple requests. 
 * The threadppol contains a queue for incoming functions (in this case client requests), worker threads that 
 * are assigned a client and handle the request. Mutex variables for the queue and worker threads, 
 * and conditional variables that determine when worker threads should join the queue. This allows the 
 * server to handle multiple requests at once while preventing shared values from being overwritten from multiple 
 * sources at the same time.
*/

class ThreadPool {
    public: 
    // Constructor with max number of threads. 
    ThreadPool(size_t numThreads);

    // Destructor which joins all threads.
    ~ThreadPool();

    /**
     * @brief Adds a new task into the queue.
     * 
     * Enqueues the function into the queue which is then picked up by a worker thread if the worker thread 
     * has completed its current task. 
     * 
     * @param task is a provided std::function that has no parameters and returns nothing. 
     */
    void enqueue(std::function<void ()> task);

    /**
     * @brief Joins all threads
     * 
     * Joins the worker threads and makes the main thread wait for the threadpool to complete its tasks. 
     */
    void threadpoolJoin();


    private:
    std::vector<std::thread> threads;               // Worker threads
    std::queue<std::function<void ()>> tasks;       // Tasks
    std::mutex mx;                                  // Mutex for queue
    std::condition_variable cond;                   // Conditional for front of queue
    size_t inUseThreads;                            // Number of worker threads in use
    bool running;                                   // Should worker threads be running. 

    /**
     * @brief worker thread loop. 
     * 
     * Base procedure of every worker thread. Calls available tasks or blocks until a task becomes available.
     * 
     */
    void workerThread();                            




};


#endif


