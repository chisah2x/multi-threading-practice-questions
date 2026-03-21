#include "ZeroEvenOdd.hpp"

ZeroEvenOdd::ZeroEvenOdd(int n) : n_(n), turn_(0) {}

void ZeroEvenOdd::zero(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n_; ++i) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return turn_ == 0; });
        printNumber(0);
        turn_ = (i % 2 == 1) ? 1 : 2;
        cv_.notify_all();
    }
}

void ZeroEvenOdd::even(std::function<void(int)> printNumber) {
    for (int i = 2; i <= n_; i += 2) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return turn_ == 2; });
        printNumber(i);
        turn_ = 0;
        cv_.notify_all();
    }
}

void ZeroEvenOdd::odd(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n_; i += 2) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return turn_ == 1; });
        printNumber(i);
        turn_ = 0;
        cv_.notify_all();
    }
}