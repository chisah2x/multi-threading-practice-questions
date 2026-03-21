#ifndef FIZZBUZZ_HPP
#define FIZZBUZZ_HPP

#include <mutex>
#include <condition_variable>
#include <functional>

class FizzBuzz {
private:
    int n;
    int current;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FizzBuzz(int n);
    void fizz(std::function<void()> printFizz);
    void buzz(std::function<void()> printBuzz);
    void fizzbuzz(std::function<void()> printFizzBuzz);
    void number(std::function<void(int)> printNumber);
};

#endif // FIZZBUZZ_HPP