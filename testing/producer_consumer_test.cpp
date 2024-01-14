#include "../src/ProducerConsumer.h"
#include <iostream>
#include <thread>
#include <cassert>

int main() {
  ProducerConsumer <int> PS(20);

  PS.add_item(1);
  auto ev = PS.get_item();

  std::cout << ev << "\n";

  return 0;
}