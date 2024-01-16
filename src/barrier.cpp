#include "barrier.h"

Barrier::Barrier(int num_threads_) : count_mutex(), turnstile(0), count(0), num_threads(num_threads_) {}

void Barrier::barrier_point() {
  count_mutex.lock();
  count++;
  count_mutex.unlock();
  if (count == num_threads) {
    turnstile.signal();
  }

  turnstile.wait();
  turnstile.signal();
}

ReusableBarrier::ReusableBarrier(int num_threads_) : Barrier(num_threads_), turnstile_close(1) {}

void ReusableBarrier::barrier_point() {
  count_mutex.lock();
  count++;
  if (count == num_threads) {
    turnstile_close.wait();
    turnstile.signal();
  }
  count_mutex.unlock();

  turnstile.wait();
  turnstile.signal();

  count_mutex.lock();
  count--;
  if (count == 0) {
    turnstile.wait();
    turnstile_close.signal();
  }
  count_mutex.unlock();

  turnstile_close.wait();
  turnstile_close.signal();
}