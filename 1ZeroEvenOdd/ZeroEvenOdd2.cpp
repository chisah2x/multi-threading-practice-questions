#include "ZeroEvenOdd2.hpp"

ZeroEvenOdd2::ZeroEvenOdd2(int n) : n_(n){}

void ZeroEvenOdd2::zero(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n_; i++)
    {
        zeroSem.acquire();  // Wait for permission to print 0 (blocks if semaphore is 0)
        printNumber(0);
        if (i % 2 == 1) {
            oddSem.release();  // Increment oddSem to allow odd thread to proceed
        } else {
            evenSem.release();  // Increment evenSem to allow even thread to proceed
        }
    }
}

void ZeroEvenOdd2::even(std::function<void(int)> printNumber) {
    for (int i = 2; i <= n_; i += 2) {
        evenSem.acquire();  // Wait for permission to print even number (blocks if semaphore is 0)
        printNumber(i);
        zeroSem.release();  // Increment zeroSem to allow zero thread to proceed
    }
}

void ZeroEvenOdd2::odd(std::function<void(int)> printNumber) {
    for (int i = 1; i <= n_; i += 2) {
        oddSem.acquire();  // Wait for permission to print odd number (blocks if semaphore is 0)
        printNumber(i);
        zeroSem.release();  // Increment zeroSem to allow zero thread to proceed
    }
}