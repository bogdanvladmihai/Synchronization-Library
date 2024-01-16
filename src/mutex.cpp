#include "mutex.h"
#include <chrono>

/*******************************************
 * Mutex 
 */
Mutex::Mutex() : flag(ATOMIC_FLAG_INIT) {}

void Mutex::lock() {
  while (std::atomic_flag_test_and_set_explicit(&flag, std::memory_order_acquire)) {}
}

void Mutex::unlock() {
  std::atomic_flag_clear_explicit(&flag, std::memory_order_release);
}

bool Mutex::try_lock() {
  return !std::atomic_flag_test_and_set_explicit(&flag, std::memory_order_acquire);
}


/*******************************************
 * TimedMutex 
 */
bool TimedMutex::try_lock_for(int ms) {
  auto start_time = std::chrono::high_resolution_clock::now();
  while (std::atomic_flag_test_and_set_explicit(&flag, std::memory_order_acquire)) {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
    if (duration.count() >= ms) {
      return false;
    }
  }
  return true;
}

/*******************************************
 * LockGuard 
 */
LockGuard::LockGuard(Mutex &lock_) : lock(lock_) {
  lock.lock();
}

LockGuard::~LockGuard() {
  lock.unlock();
}


/*******************************************
 * ScopedLock 
 */
ScopedLock::ScopedLock(const std::vector<std::reference_wrapper<Mutex>> &locks_) : locks(locks_) {
  for (auto &lock : locks) {
    lock.get().lock();
  }
}

ScopedLock::~ScopedLock() {
  for (auto &lock : locks) {
    lock.get().unlock();
  }
}