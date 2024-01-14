#include "semaphore.h"
#include <deque>

template <class T>
class ProducerConsumer {
private:
  std::deque<T> items;
  Mutex mutex;
  Semaphore available_items;
  Semaphore free_spaces;

  // TODO Cristiana: items should keep references to the items

public:
  ProducerConsumer(int buff_size);
  void add_item(const T& item);
  T get_item();
};

#include "ProducerConsumer.cpp"