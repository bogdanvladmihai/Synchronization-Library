#include "mutex.h"

/**
 * Semaphore class
 * ------------------------------------------------------
 * int n = 10;
 * Semaphore sem(n);
 * 
 * sem.wait();
 * critical zone
 * sem.signal();
 */
class Semaphore {
public:
  Semaphore(int);
  void signal();
  void wait();
  
  Semaphore(const Semaphore &) = delete;
  Semaphore operator = (const Semaphore&) = delete;
  ~Semaphore() = default;

private:
  int count;
  Mutex lock;

  static const int TRY_NO_TIMEOUT_CNT = 10000;
};

