#include "../src/ProducerConsumer.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <algorithm>
#include <numeric>

int main() {
  const int WORKERS = 1e5;
  const int ITEMS = 50;

  ProducerConsumer <int> PS(ITEMS);

  std::vector<int> items;
  std::vector<int> l(WORKERS);
  std::iota(l.begin(), l.end(), 0);
  for (int &i : l) {
    if (i % 2 == 0) {
      std::thread t([&PS, &i]() {
        PS.add_item(i);
      });
    } else {
      std::thread t([&PS, i, &items]() {
        int item = PS.get_item();
        items.push_back(item);
      });
    }
  }

  assert(std::is_sorted(items.begin(), items.end()) && items.size() == WORKERS / 2);
  std::cout << "Test passed!" << std::endl;

  return 0;
}