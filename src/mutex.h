#include <atomic>
#include <vector>
#include <functional>
#include <chrono>

/**
 * Mutex class
 * ------------------------------------------------------
 * Mutex lock;
 * lock.lock();
 * lock.unlock();
 * 
 * if (lock.try_lock()) {
 *   critical zone
 *   lock.unlock();
 * } else {
 *   non critical zone
 * }
 */
class Mutex {
public:
  Mutex();
  ~Mutex() = default;
  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  void lock();
  void unlock();
  bool try_lock();

protected:
  std::atomic_flag flag;
};


/**
 * TimedMutex class (derived from Mutex)
 * ------------------------------------------------------
 * TimedMutex lock;
 * lock.try_lock_for(numer of milliseconds)
 */
class TimedMutex : public Mutex {
public:
  TimedMutex() = default;
  ~TimedMutex() = default;
  TimedMutex(const TimedMutex&) = delete;
  TimedMutex& operator=(const TimedMutex&) = delete;

  bool try_lock_for(int ms);
};

/**
 * LockGuard class
 * ------------------------------------------------------
 * Mutex counter_lock;
 * int count = 0;
 * 
 * bool add_one() {
 *   LockGuard lock(counter_lock);
 *   critical zone
 *   if (count == LIMIT) {
 *    return false;
 *   }
 *   count += 1;
 *   return true;
 * }
 */
class LockGuard {
public:
  LockGuard(Mutex&);
  ~LockGuard();

private:
  Mutex &lock;
};


/**
 * ScopedLock class
 * ------------------------------------------------------
 * Mutex m1, m2, m3;
 * 
 * void func() {
 *   vector<Mutex&> guards = {m1, m2, m3};
 *   ScopedLock lock(guards);
 *   cricital zone
 * }
 */
class ScopedLock {
public:
  ScopedLock(const std::vector<std::reference_wrapper<Mutex>>&);
  ~ScopedLock();

private:
  std::vector<std::reference_wrapper<Mutex>> locks;
};