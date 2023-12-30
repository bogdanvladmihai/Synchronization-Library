#include "../src/mutext.h"
#include <iostream>
#include <thread>
#include <cassert>

int main() {
  const int WORKERS = 100;
  const int TO_ADD = 1e5;

  Mutex counter_lock;
  int count = 0;

  std::vector<std::thread> workers;

  for (int i = 0; i < WORKERS; i++) {
    workers.push_back(std::thread([&]() {
      for (int j = 0; j < TO_ADD; j++) {
        counter_lock.lock();
        count += 1;
        counter_lock.unlock();
      }
    }));
  }

  for (std::thread &worker : workers) {
    worker.join();
  }

  std::cout << "Expected: " << WORKERS * TO_ADD << std::endl;
  std::cout << "Actual: " << count << std::endl;
  assert(count == WORKERS * TO_ADD);

  return 0;
}