#include "semaphore.h"

class Lightswitch {
private:
  int counter;
  Mutex mutex;
public:
  Lightswitch() : counter(0) {}
  void close(Semaphore& s);
  void open(Semaphore& s);
};