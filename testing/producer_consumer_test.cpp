#include "../src/ProducerConsumer.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <algorithm>
#include <numeric>

int main() {
  const int WORKERS = 10000;
  const int ITEMS = 5;

  ProducerConsumer <int> PS(ITEMS);

  std::vector<int> items;
  std::vector<std::thread> threads;
  Mutex items_mutex;

  for (int i = 0; i < WORKERS; i++) {
    if (i % 2 == 1) {
      threads.push_back(std::thread ([&PS, i]() {
        PS.add_item(i);
      }));
    } else {
      threads.push_back(std::thread ([&PS, i, &items, &items_mutex]() {
        int item = PS.get_item();

        items_mutex.lock();
        items.push_back(item);
        items_mutex.unlock();
      }));
    }
  }

  for(auto &t: threads){
    t.join();
  }
  assert(items.size() == WORKERS / 2);
  assert(std::is_sorted(items.begin(), items.end()));
  std::cout << "Test passed!" << std::endl;

  return 0;
}