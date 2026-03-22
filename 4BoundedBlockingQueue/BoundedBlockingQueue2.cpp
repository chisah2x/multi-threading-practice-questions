// boundedblockingqueue2.cpp
#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class BoundedBlockingQueue2 {
    private:
    int capacity;
    std::queue<int> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    explicit BoundedBlockingQueue2(int cap) : capacity(cap){}

    void enqueue(int element)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return queue.size() < capacity;});
        queue.push(element);
        cv.notify_all();
    }

    int dequeue()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return !queue.empty();});
        int element = queue.front();
        queue.pop();
        cv.notify_all();
        return element;
    }

    int size()
    {
        std::unique_lock<std::mutex> lock(mtx);
        int queueSize = queue.size();
        lock.unlock();
        return queueSize;
    }
};

int main()
{
    const int capacity = 5;
    const int itemsPerProducer = 8;
    const int numProducers = 3;
    const int numConsumers = 2;

    BoundedBlockingQueue2 queue(capacity);
    std::mutex coutMutex;

    auto producer = [&](int start, int prodId) {
        for (int i = start; i < start + itemsPerProducer; i++) {
            queue.enqueue(i);
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "[Producer " << prodId << "] enqueued " << i << "\n";
            }
        }
        };

    auto consumer = [&](int consId) {
        while (true) {
            int item = queue.dequeue();
            if (item == -1) break;

            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "[Consumer " << consId << "] dequeued " << item << "\n";
            }
        }
        };

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < numProducers; i++) producers.emplace_back(producer, i * itemsPerProducer, i);
    for (int i = 0; i < numConsumers; i++) consumers.emplace_back(consumer, i);

    for (auto& prod : producers) prod.join();

    //Send exactly enough poison pills for the consumers
    std::cout << "--- All data produced. Sending poison pills. ---\n";
    for (int i = 0; i < numConsumers; i++) {
        queue.enqueue(-1);
    }

    //Now join consumers
    for (auto& cons : consumers) cons.join();

    std::cout << "\nAll done. Final queue size = " << queue.size() << "\n";
    return 0;
}