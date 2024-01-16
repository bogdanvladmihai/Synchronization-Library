#include "semaphore.h"
#include <thread>
#include <chrono>

/*******************************************
 * Semaphore 
 */
Semaphore::Semaphore(int count_) : count(count_) {}

void Semaphore::signal() {
  lock.lock();
  count++;
  lock.unlock();
}

void Semaphore::wait() {
  for (int i = 0; i < TRY_NO_TIMEOUT_CNT; i++) {
    lock.lock();
    if (count > 0) {
      count--;
      lock.unlock();
      return;
    }
    lock.unlock();
  }

  while (true) {
    lock.lock();
    if (count > 0) {
      count--;
      lock.unlock();
      return;
    }
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
}