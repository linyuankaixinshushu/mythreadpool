#include "nomutexqueue.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
int main() {
    nomutexqueue<int> a;
    for(int i = 0; i < 1000000; i++) {
        a.Enqueue(3);
        a.Enqueue(4);
        a.Enqueue(5);
    }
    std::mutex vector_write_mutex;
    std::vector<std::thread> threads;
    std::vector<int> result;

    for(int i = 0; i < 10; i++) {
        threads.push_back(std::thread([&]() {
            for(int k = 0; k < 300000; k++) {
                int j = a.Dequeue();
                vector_write_mutex.lock();
                result.push_back(j);
                vector_write_mutex.unlock();
            }
        })
        );
    }
    for(auto & j : threads) {
        j.join();
    }
    int f = 0;
    int b = 0;
    int c = 0;
    for(auto d : result) {
        if(d == 3) {
            f++;
        }
        else if(d == 4) {
            b++;
        }
        else {
            c++;
        }
    }
    std::cout << "3 : " << f << std::endl;
    std::cout << "4 : " << b << std::endl;
    std::cout << "5 : " << c << std::endl;
    std::cout << "vector size : " << result.size();
}
