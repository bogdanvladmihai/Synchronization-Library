#include "../src/semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

void think() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::mt19937::result_type> dist(50, 100);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void eat() {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<std::mt19937::result_type> dist(10, 20);
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void get_chopsticks(int id, Semaphore& sem, std::vector<Mutex> &chopsticks) {
  sem.wait();
  chopsticks[id].lock();
  chopsticks[(id + 1) % chopsticks.size()].lock();
}

void put_chopsticks(int id, Semaphore& sem, std::vector<Mutex> &chopsticks) {
  chopsticks[id].unlock();
  chopsticks[(id + 1) % chopsticks.size()].unlock();
  sem.signal();
}

int main() {
  const int PHILOSOPHERS = 5;
  std::vector<std::thread> threads;

  Semaphore sem(PHILOSOPHERS - 1);

  std::vector<Mutex> chopsticks(PHILOSOPHERS);
  for (int i = 0; i < PHILOSOPHERS; i++) {
    threads.push_back(std::thread([&] {
      auto time_after_15_seconds = std::chrono::steady_clock::now() + std::chrono::seconds(15);
      while (std::chrono::steady_clock::now() < time_after_15_seconds) {
        think();
        get_chopsticks(i, std::ref(sem), std::ref(chopsticks));
        eat();
        put_chopsticks(i, std::ref(sem), std::ref(chopsticks));
      }
    }));
  }

  for (auto &worker : threads) {
    worker.join();
  }

  std::cout << "Success!\n";

  return 0;
}