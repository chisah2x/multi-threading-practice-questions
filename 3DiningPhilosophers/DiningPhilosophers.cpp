#include "DiningPhilosophers.hpp"

DiningPhilosophers::DiningPhilosophers() {
    // Constructor
}

void DiningPhilosophers::wantsToEat(int philosopher,
                                     std::function<void()> pickLeftFork,
                                     std::function<void()> pickRightFork,
                                     std::function<void()> eat,
                                     std::function<void()> putLeftFork,
                                     std::function<void()> putRightFork) 
                                     
{
    //Limit number of threads tried to eat simultaneously
    table.acquire(); 

    //Indentify forks
    int left = philosopher;
    int right = (philosopher+1)%5;

    //Acquire both resources(fork)
    forks[left].lock();
    forks[right].lock();

    //Perform eating process
    pickLeftFork();
    pickRightFork();
    eat();

    //Put down forks
    putLeftFork();
    putRightFork();

    forks[left].unlock();
    forks[right].unlock();
    
    table.release();
}