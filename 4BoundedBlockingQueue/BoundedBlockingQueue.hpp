#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBlockingQueue
{
    private:
    int capacity;
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cv;
    public:

    BoundedBlockingQueue(int capacity);

    void enqueue(int element);

    int dequeue();

    int size();
};
        