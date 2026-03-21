// 1116. Print Zero Even Odd
// https://leetcode.com/problems/print-zero-even-odd/description/
// You have a function printNumber that can be called with an integer parameter and prints it to the console.
//
// For example, calling printNumber(7) prints 7 to the console.
//
// You are asked to design three functions: zero, even, and odd. All of them take a function printNumber as a parameter.
//
// The same instance of ZeroEvenOdd will be passed to three different threads:
//
// Thread A: calls zero() that should only output 0's.
// Thread B: calls even() that should only output even numbers.
// Thread C: calls odd() that should only output odd numbers.
//
// Modify the given class to make the three threads print the numbers in order: 010203040506... where the length of the output string is 2*n.
//
// Constraints:
// 1 <= n <= 1000

#ifndef ZEROEVENODD_HPP
#define ZEROEVENODD_HPP

#include <functional>
#include <mutex>
#include <condition_variable>

class ZeroEvenOdd {
private:
    int n_;
    std::mutex mtx_;
    std::condition_variable cv_;
    int turn_;  // 0: zero's turn, 1: odd's turn, 2: even's turn

public:
    ZeroEvenOdd(int n);
    void zero(std::function<void(int)> printNumber);
    void even(std::function<void(int)> printNumber);
    void odd(std::function<void(int)> printNumber);
};

#endif // ZEROEVENODD_HPP