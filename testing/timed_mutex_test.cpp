#include "../src/mutex.h"
#include <iostream>
#include <thread>
#include <cassert>

int main() {
  TimedMutex mutex;

  mutex.lock();
  std::thread t([&mutex]() {
    assert(mutex.try_lock_for(100) == false);
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  mutex.unlock();
  t.join();

  mutex.lock();
  std::thread t2([&mutex]() {
    assert(mutex.try_lock_for(1000) == true);
  });
  mutex.unlock();
  t2.join();

  std::cout << "Success!\n";

  return 0;
}