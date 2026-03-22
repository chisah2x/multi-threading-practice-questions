#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>

class MultiThread {
private:
public:
    MultiThread() {}
    
    void performAction(int philosopher, std::function<void()> pickLeft, std::function<void()> pickRight, std::function<void()> eat) {
        
    }
};

// int main() {
//     MultiThread mt;
//     std::vector<std::jthread> threads;
//     std::mutex cout_mutex; // For synchronized output
    
//     for (int i = 0; i < 5; ++i) {
//         threads.emplace_back([&, i]() {
//             auto pickLeft = [&]() { 
//                 std::lock_guard<std::mutex> lock(cout_mutex);
//                 std::cout << "Philosopher " << i << " picks left fork" << std::endl; 
//             };
//             auto pickRight = [&]() { 
//                 std::lock_guard<std::mutex> lock(cout_mutex);
//                 std::cout << "Philosopher " << i << " picks right fork" << std::endl; 
//             };
//             auto eat = [&]() { 
//                 std::lock_guard<std::mutex> lock(cout_mutex);
//                 std::cout << "Philosopher " << i << " eats" << std::endl; 
//             };
//             mt.performAction(i, pickLeft, pickRight, eat);
//         });
//     }

//     // for (int i = 0; i < 5; ++i) {
//     //     auto pickLeft = [&, i]() { 
//     //         std::lock_guard<std::mutex> lock(cout_mutex);
//     //         std::cout << "Philosopher " << i << " picks left fork" << std::endl; 
//     //     };
//     //     auto pickRight = [&, i]() { 
//     //         std::lock_guard<std::mutex> lock(cout_mutex);
//     //         std::cout << "Philosopher " << i << " picks right fork" << std::endl; 
//     //     };
//     //     auto eat = [&, i]() { 
//     //         std::lock_guard<std::mutex> lock(cout_mutex);
//     //         std::cout << "Philosopher " << i << " eats" << std::endl; 
//     //     };
//     //     threads.emplace_back(&MultiThread::performAction, &mt, i, pickLeft, pickRight, eat);
//     // }
    
//     // for (auto& t : threads) {
//     //     t.join();
//     // }
    
//     return 0;
// }