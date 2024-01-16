#include "semaphore.h"

class Barrier {
public:
  Barrier(int num_threads_);
  Barrier(const Barrier &other) = delete;
  Barrier &operator=(const Barrier &other) = delete;
  ~Barrier() = default;

  virtual void barrier_point();
protected:
  Mutex count_mutex;
  Semaphore turnstile;
  int count, num_threads;
};

class ReusableBarrier : public Barrier {
public:
  ReusableBarrier(int num_threads_);
  ReusableBarrier(const ReusableBarrier &other) = delete;
  ReusableBarrier &operator=(const ReusableBarrier &other) = delete;
  ~ReusableBarrier() = default;

  void barrier_point() override;
private:
  Semaphore turnstile_close;
};