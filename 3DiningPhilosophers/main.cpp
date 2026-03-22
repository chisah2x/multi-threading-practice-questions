//#include "DiningPhilosophers.hpp"
//#include <iostream>
//#include <vector>
//#include <thread>
//#include <mutex>
//
//int main() {
//    DiningPhilosophers dp;
//    std::vector<std::vector<int>> output;
//
//    std::mutex output_mutex;
//    int n = 2; // Number of times each philosopher eats
//
//    // Create threads for each philosopher
//    std::vector<std::thread> threads;
//    for (int i = 0; i < 5; ++i) 
//    {
//        threads.emplace_back(
//            [&, i]() 
//        {
//            // Define lambdas for this philosopher
//            auto pickLeftFork = [&]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({i, 1, 1}); // philosopher, fork 1 (left), pick
//            };
//            auto pickRightFork = [&]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({i, 2, 1}); // philosopher, fork 2 (right), pick
//            };
//            auto eat = [&]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({i, 0, 3}); // philosopher, 0, eat
//            };
//            auto putLeftFork = [&]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({i, 1, 2}); // philosopher, fork 1, put
//            };
//            auto putRightFork = [&]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({i, 2, 2}); // philosopher, fork 2, put
//            };
//
//            for (int j = 0; j < n; ++j) {
//                dp.wantsToEat(i, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork);
//            }
//        });
//    }
//
//    // Wait for all threads to finish
//    for (auto& t : threads) {
//        t.join();
//    }
//
//    // Print the output
//    std::cout << "Output actions:" << std::endl;
//    for (const auto& action : output) {
//        std::cout << "[" << action[0] << "," << action[1] << "," << action[2] << "]" << std::endl;
//    }
//
//    return 0;
//}
//

#include "DiningPhilosophers.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int main() {
    DiningPhilosophers dp;

    std::cout << "Number of times each philosopher eats: " << std::endl;
    int n;
    std::cin >> n;

    const int NUM_PHILOSOPHERS = 5;
    const int EAT_TIMES = n;

    //Create threads for each philosopher
    std::vector<std::thread> philosophers;
    philosophers.reserve(NUM_PHILOSOPHERS);
    std::vector<std::vector<int>> output;
    std::mutex output_mutex;


    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back([i, &output, &output_mutex, &dp, EAT_TIMES]() {

            auto pickLeftFork = [i, &output, &output_mutex]() {
                std::lock_guard<std::mutex> lock(output_mutex);
                output.push_back({ i,1,1 }); // philosopher, fork 1 (left), pick
                };

            auto pickRightFork = [i, &output, &output_mutex]() {
                std::lock_guard<std::mutex> lock(output_mutex);
                output.push_back({ i,2,1 }); // philosopher, fork 1 (left), pick
                };

            auto eat = [i, &output, &output_mutex]() {
                std::lock_guard<std::mutex> lock(output_mutex);
                output.push_back({ i, 0, 3 }); // philosopher, 0, eat
                };
            auto putLeftFork = [i, &output, &output_mutex]() {
                std::lock_guard<std::mutex> lock(output_mutex);
                output.push_back({ i, 1, 2 }); // philosopher, fork 1, put
                };
            auto putRightFork = [i, &output, &output_mutex]() {
                std::lock_guard<std::mutex> lock(output_mutex);
                output.push_back({ i, 2, 2 }); // philosopher, fork 2, put
                };

            for (int round = 0; round < EAT_TIMES; round++)
            {
                dp.wantsToEat(i, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork);
            }

            });
    }

    for (auto& t : philosophers) {
        t.join();
    }

    //Print the output
    std::cout << "Output actions:" << std::endl;
    for (const auto& action : output) {
        std::cout << "[" << action[0] << "," << action[1] << "," << action[2] << "]" << std::endl;
    }

    return 0;
}
//
//#include "DiningPhilosophers.hpp"
//#include <iostream>
//#include <vector>
//#include <thread>
//#include <mutex>
//
//int main() {
//    DiningPhilosophers dp;
//
//    std::cout << "Number of times each philosopher eats: " << std::endl;
//    int n;
//    std::cin >> n;
//
//    const int NUM_PHILOSOPHERS = 5;
//    const int EAT_TIMES = n;
//
//    // Use jthread so destructor requests stop() and joins automatically
//    std::vector<std::jthread> philosophers;
//    philosophers.reserve(NUM_PHILOSOPHERS);
//    std::vector<std::vector<int>> output;
//    std::mutex output_mutex;
//
//    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
//    {
//        philosophers.emplace_back([i, &output, &output_mutex, &dp, EAT_TIMES](std::stop_token st) {
//
//            auto pickLeftFork = [i, &output, &output_mutex]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({ i,1,1 });
//                };
//
//            auto pickRightFork = [i, &output, &output_mutex]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({ i,2,1 });
//                };
//
//            auto eat = [i, &output, &output_mutex]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({ i, 0, 3 });
//                };
//            auto putLeftFork = [i, &output, &output_mutex]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({ i, 1, 2 });
//                };
//            auto putRightFork = [i, &output, &output_mutex]() {
//                std::lock_guard<std::mutex> lock(output_mutex);
//                output.push_back({ i, 2, 2 });
//                };
//
//            for (int round = 0; round < EAT_TIMES && !st.stop_requested(); ++round)
//            {
//                // ensure wantsToEat will eventually return or respect stop_token/cancellation
//                dp.wantsToEat(i, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork);
//            }
//
//            });
//    }
//
//    // Destroy jthreads (joins) before printing results.
//    // Either let the vector go out of scope, or explicitly clear to join now:
//    philosophers.clear(); // destructor of each jthread requests stop() and joins
//
//    // Print the output
//    std::cout << "Output actions:" << std::endl;
//    for (const auto& action : output) {
//        std::cout << "[" << action[0] << "," << action[1] << "," << action[2] << "]" << std::endl;
//    }
//
//    return 0;
//}