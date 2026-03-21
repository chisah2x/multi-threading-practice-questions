#include "FizzBuzz.hpp"
#include <iostream>
#include <thread>

int main() {
    FizzBuzz fb(30);

    std::thread t1(&FizzBuzz::fizz, &fb, []() { std::cout << "fizz" << std::endl; });
    std::thread t2(&FizzBuzz::buzz, &fb, []() { std::cout << "buzz" << std::endl; });
    std::thread t3(&FizzBuzz::fizzbuzz, &fb, []() { std::cout << "fizzbuzz" << std::endl; });
    std::thread t4(&FizzBuzz::number, &fb, [](int num) { std::cout << num << std::endl; });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}