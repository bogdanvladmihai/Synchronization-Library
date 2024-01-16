#include "../src/ProducerConsumer.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <numeric>
#include <set>

int main() {
  const int WORKERS = 10000;
  const int ITEMS = 5;

  ProducerConsumer <int> PS(ITEMS);

  std::vector<std::thread> threads;
  Mutex items_mutex;
  std::set<int> items;
  for (int i = 0; i < WORKERS; i++) {
    if (i % 2 == 1) {
      threads.push_back(std::thread ([&PS, i]() {
        PS.add_item(i);
      }));
    } else {
      threads.push_back(std::thread ([&PS, i, &items, &items_mutex]() {
        int item = PS.get_item();

        items_mutex.lock();
        items.insert(item);
        items_mutex.unlock();
      }));
    }
  }

  for(auto &t: threads){
    t.join();
  }

  assert(items.size() == WORKERS / 2);
  for (int i = 0; i < WORKERS / 2; i++) {
    assert(items.find(2 * i + 1) != items.end());
  }
  std::cout << "Test passed!" << std::endl;

  return 0;
}