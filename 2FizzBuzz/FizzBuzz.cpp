#include "FizzBuzz.hpp"

FizzBuzz::FizzBuzz(int n) : n(n), current(1) {}

void FizzBuzz::fizz(std::function<void()> printFizz) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() {
            return current > n || (current % 3 == 0 && current % 5 != 0);
        });
        if (current > n) break;
        printFizz();
        current++;
        lock.unlock();
        cv.notify_all();
    }
}

void FizzBuzz::buzz(std::function<void()> printBuzz) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() {
            return current > n || (current % 3 != 0 && current % 5 == 0);
        });
        if (current > n) break;
        printBuzz();
        current++;
        lock.unlock();  
        cv.notify_all();
    }
}

void FizzBuzz::fizzbuzz(std::function<void()> printFizzBuzz) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() {
            return current > n || (current % 15 == 0);
        });
        if (current > n) break;
        printFizzBuzz();
        current++;
        lock.unlock();
        cv.notify_all();
    }
}

void FizzBuzz::number(std::function<void(int)> printNumber) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() {
            return current > n || (current % 3 != 0 && current % 5 != 0);
        });
        if (current > n) break;
        printNumber(current);
        current++;
        lock.unlock();
        cv.notify_all();
    }
}