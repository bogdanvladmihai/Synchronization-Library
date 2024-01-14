#include "lightswitch.h"

void Lightswitch::open(Semaphore& s) {
  LockGuard lock(mutex);
  counter--;
  if (counter == 0) {
    s.signal();
  }
}

void Lightswitch::close(Semaphore& s) {
  LockGuard lock(mutex);
  counter++;
  if (counter == 1) {
    s.wait();
  }
}