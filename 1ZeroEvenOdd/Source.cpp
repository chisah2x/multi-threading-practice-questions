#include <iostream>
#include <thread>
#include "ZeroEvenOdd.hpp"
#include "ZeroEvenOdd2.hpp"

int main()
{
	ZeroEvenOdd obj1(5);
	ZeroEvenOdd2* obj2 = new ZeroEvenOdd2(10);  

	std::function<void(int)> print = [](int x) { std::cout << x << " "; };
	// auto print = [](int x) { std::cout << x << " "; };

	// Test ZeroEvenOdd (mutex-based)
	{
		std::thread t0(&ZeroEvenOdd::zero, &obj1, print);
		std::thread t1(&ZeroEvenOdd::odd, &obj1, print);
		std::thread t2(&ZeroEvenOdd::even, &obj1, print);

		t0.join();
		t1.join();
		t2.join();
	}

	std::cout << std::endl;

	// Test ZeroEvenOdd2 (semaphore-based)
	{
		std::thread t0(&ZeroEvenOdd2::zero, obj2, print);
		std::thread t1(&ZeroEvenOdd2::odd, obj2, print);
		std::thread t2(&ZeroEvenOdd2::even, obj2, print);

		t0.join();
		t1.join();
		t2.join();
	}

	std::cout << std::endl;

	return 0;
}