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

private:
  int count;
  Mutex lock;
};

