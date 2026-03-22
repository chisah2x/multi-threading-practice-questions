#include "BoundedBlockingQueue.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// static std::mutex coutMutex;

int main()
{
    const int capacity = 5;
    const int itemsPerProducer = 8;
    const int numProducers = 3;
    const int numConsumers = 3;

    BoundedBlockingQueue queue(capacity);

    std::mutex coutMutex;

    auto producer = [&](int start, int prodId)
    {
        for(int i=start; i<start+itemsPerProducer; i++)
        {
            queue.enqueue(i); 

            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "[Producer "<< prodId << " ] enqueue " << i << " (queue size = )" << queue.size() << ")\n";
            }
        }
    };

    auto consumer = [&](int consId)
    {
        //When one only one consumer is present, we can simply loop for the total number of items produced (numProducers*itemsPerProducer) and call dequeue that many times. 
        // for(int i=0; i<numProducers*itemsPerProducer; i++)
        //
        for(int i=0; i< itemsPerProducer; i++)
        {
            int item = queue.dequeue();

            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "[Consumer "<< consId << " ]  dequeue " << item << " (queue size = " << queue.size() << ")\n";
            }
        }
    };

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for(int i=0; i<numProducers; i++)
    {
        producers.emplace_back(producer, i*itemsPerProducer, i);
    }

    for(int i=0; i<numConsumers; i++)
    {
        consumers.emplace_back(consumer, i);
    }

    for(auto& prod : producers) prod.join();

    for(auto& cons: consumers) cons.join();

    std::cout << "\nAll done. Final queue size = " << queue.size() << "\n";

    return 0;
}