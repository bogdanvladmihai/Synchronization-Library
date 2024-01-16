#include "../src/barrier.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <numeric>

int main() {
  const int WORKERS = 100;

  Barrier barrier(WORKERS);
  std::vector<int> v, v2;
  std::vector<std::thread> threads;

  Mutex v_mutex;

  std::vector<int> perm(WORKERS);
  std::iota(perm.begin(), perm.end(), 0);
  for (int &i : perm) {
    threads.push_back(std::thread([&v, &i, &barrier, &v_mutex, &v2]() {
      v_mutex.lock();
      v.push_back(i);
      v_mutex.unlock();

      barrier.barrier_point();
      
      v_mutex.lock();
      v.push_back(i);
      v_mutex.unlock();

      barrier.barrier_point();

      v_mutex.lock();
      v2.push_back(i);
      v_mutex.unlock();
    }));
  }

  for (auto &t : threads) {
    t.join();
  }

  assert(v.size() == 2 * WORKERS);
  assert(std::is_permutation(v.begin(), v.begin() + WORKERS, perm.begin()));
  assert(std::is_permutation(v.begin() + WORKERS, v.end(), perm.begin()));
  assert(v2.size() == WORKERS);
  assert(std::is_permutation(v2.begin(), v2.end(), perm.begin()));
  std::cout << "Test passed!" << std::endl;

  return 0;
}