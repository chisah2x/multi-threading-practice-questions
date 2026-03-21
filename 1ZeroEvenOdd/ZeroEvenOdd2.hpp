#ifndef ZEROEVENODD2_HPP
#define ZEROEVENODD2_HPP

#include <functional>
#include <semaphore>

class ZeroEvenOdd2 {
private:
    int n_;
    std::binary_semaphore zeroSem{ 1 };
    std::binary_semaphore oddSem{ 0 };
    std::binary_semaphore evenSem{ 0 };

public:
    ZeroEvenOdd2(int n);
    void zero(std::function<void(int)> printNumber);
    void even(std::function<void(int)> printNumber);
    void odd(std::function<void(int)> printNumber);
};

#endif // ZEROEVENODD2_HPP