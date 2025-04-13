/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex fork0;
std::mutex fork1;

void think(int id) {
    std::cout << "Philosopher " << id << " is thinking...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void eat(int id) {
    std::cout << "Philosopher " << id << " is eating!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Philosopher " << id << " is done eating.\n";
}

void philosopher(int id) {
    for (int i = 0; i < 5; ++i) { // repeat eating/thinking 5 times
        think(id);

        if (id == 0) {
            // Philosopher 0: Lock fork0 then fork1
            std::lock_guard<std::mutex> lockLeft(fork0);
            std::lock_guard<std::mutex> lockRight(fork1);
            eat(id);
        } else {
            // Philosopher 1: Lock fork1 then fork0
            std::lock_guard<std::mutex> lockRight(fork1);
            std::lock_guard<std::mutex> lockLeft(fork0);
            eat(id);
        }
    }
}

int main() {
    std::thread phil0(philosopher, 0);
    std::thread phil1(philosopher, 1);

    phil0.join();
    phil1.join();

    return 0;
}
