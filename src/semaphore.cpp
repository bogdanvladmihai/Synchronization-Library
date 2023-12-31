#include "semaphore.h"

/*******************************************
 * Semaphore 
 */
Semaphore::Semaphore(int count_) : count(count_) {}

void Semaphore::signal() {
  LockGuard guard(lock);
  count++;
}

void Semaphore::wait() {
  while (true) {
    LockGuard guard(lock);
    if (count > 0) {
      count--;
      return;
    }
  }
}