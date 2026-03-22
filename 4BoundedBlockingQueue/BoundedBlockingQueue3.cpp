#include <iostream>
#include <queue>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>
#include <chrono>

template <typename T>
class SemaphoreBoundedQueue {
private:
    std::queue<T> queue_;
    std::mutex mtx_;

    std::counting_semaphore<> empty_slots_;
    std::counting_semaphore<> full_slots_;

public:
    explicit SemaphoreBoundedQueue(ptrdiff_t capacity)
        : empty_slots_(capacity), 
        full_slots_(0)         
    {
    }

    void produce(T item) {
        empty_slots_.acquire();

        // Lock the mutex to safely modify the queue
        {
            std::lock_guard<std::mutex> lock(mtx_);
            queue_.push(std::move(item));
            std::cout << "[Producer " << std::this_thread::get_id()
                << "] Produced: " << queue_.back()
                << " | Queue size: " << queue_.size() << "\n";
        }

        // Signal that a new item is available (increments full_slots_)
        full_slots_.release();
    }

    T consume() {
        // If full_slots_ is 0, this blocks until a producer releases one.
        full_slots_.acquire();

        T item;
        // Lock the mutex to safely modify the queue
        {
            std::lock_guard<std::mutex> lock(mtx_);
            item = std::move(queue_.front());
            queue_.pop();
            std::cout << "  [Consumer " << std::this_thread::get_id()
                << "] Consumed: " << item
                << " | Queue size: " << queue_.size() << "\n";
        }

        // 3. Signal that an empty slot is now available (increments empty_slots_)
        empty_slots_.release();

        return item;
    }
};

int main() {
    const ptrdiff_t MAX_CAPACITY = 5;
    const int NUM_PRODUCERS = 3;
    const int NUM_CONSUMERS = 2;
    const int ITEMS_PER_PRODUCER = 4;

    SemaphoreBoundedQueue<int> bq(MAX_CAPACITY);

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    auto produce = [&](int ithProd) {
        for (int i = 1; i <= ITEMS_PER_PRODUCER; i++) {
            bq.produce((ithProd * 100) + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        };

    auto consume = [&](int count) {
        for (int i = 0; i < count; ++i) {
            bq.consume();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        };

    // --- Thread Creation ---

    // Calculate how many items each consumer should process
    int items_to_consume = (NUM_PRODUCERS * ITEMS_PER_PRODUCER) / NUM_CONSUMERS;

    // 1. Start Multiple Consumers
    for (int c = 1; c <= NUM_CONSUMERS; ++c) {
        consumers.emplace_back(consume, items_to_consume);
    }

    // 2. Start Multiple Producers
    for (int p = 1; p <= NUM_PRODUCERS; ++p) {
        producers.emplace_back(produce, p);
    }

    // --- Join Threads ---

    for (auto& prod : producers) prod.join();
    for (auto& cons : consumers) cons.join();

    std::cout << "All items produced and consumed successfully.\n";
    return 0;
}