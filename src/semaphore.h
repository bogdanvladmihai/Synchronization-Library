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
  
  // TODO Vlad: thould delete op=, cc

private:
  int count;
  Mutex lock;
};

