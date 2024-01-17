#include "semaphore.h"

/**
 * 
 * Semaphore s;
 * Lightswitch L;
 * 
 * L.close(s);
 * L.open(s);
 * 
 */
class Lightswitch {
private:
  int counter;
  Mutex mutex;
public:
  Lightswitch() : counter(0) {}
  void close(Semaphore& s);
  void open(Semaphore& s);
};