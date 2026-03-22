#include "BoundedBlockingQueue.hpp"

BoundedBlockingQueue::BoundedBlockingQueue(int capacity) : capacity(capacity)
{
}

void BoundedBlockingQueue::enqueue(int element)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this](){return queue.size() < capacity;});
    queue.push(element);
    cv.notify_all();
}

int BoundedBlockingQueue::dequeue()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this](){return !queue.empty();});
    int element = queue.front();
    queue.pop();
    cv.notify_all();
    return element;
}

int BoundedBlockingQueue::size()
{
    std::unique_lock<std::mutex> lock(mtx);
    int queueSize = queue.size();
    lock.unlock();
    return queueSize;
}