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

  template<class R, class P>
  bool try_lock_for(const std::chrono::duration<R, P> &);
  template<class R, class P>
  bool try_lock_until(const std::chrono::time_point<R, P> &);
};

/**
 * LockGuard class
 * ------------------------------------------------------
 * Mutex counter_lock;
 * int count = 0;
 * 
 * void add_one() {
 *   LockGuard lock(counter_lock);
 *   count += 1;
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